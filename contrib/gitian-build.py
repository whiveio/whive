#!/usr/bin/env python3
# Copyright (c) 2018-2020 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

import argparse
import os
import subprocess
import sys

def setup():
    global args, workdir
    programs = ['ruby', 'git', 'make', 'wget', 'curl']
    if args.kvm:
        programs += ['apt-cacher-ng', 'python-vm-builder', 'qemu-kvm', 'qemu-utils']
    elif args.docker:
        if not os.path.isfile('/lib/systemd/system/docker.service'):
            dockers = ['docker.io', 'docker-ce']
            for i in dockers:
                return_code = subprocess.call(['sudo', 'apt-get', 'install', '-qq', i])
                if return_code == 0:
                    break
            if return_code != 0:
                print('Cannot find any way to install Docker.', file=sys.stderr)
                sys.exit(1)
    else:
        programs += ['lxc', 'debootstrap']
    subprocess.check_call(['sudo', 'apt-get', 'install', '-qq'] + programs)
    if not os.path.isdir('gitian.sigs'):
        subprocess.check_call(['git', 'clone', 'https://github.com/bitcoin-core/gitian.sigs.git'])
    if not os.path.isdir('bitcoin-detached-sigs'):
        subprocess.check_call(['git', 'clone', 'https://github.com/bitcoin-core/bitcoin-detached-sigs.git'])
    if not os.path.isdir('gitian-builder'):
        subprocess.check_call(['git', 'clone', 'https://github.com/devrandom/gitian-builder.git'])
    if not os.path.isdir('whive'):
        subprocess.check_call(['git', 'clone', 'https://github.com/whiveio/whive.git'])
    os.chdir('gitian-builder')
    make_image_prog = ['bin/make-base-vm', '--suite', 'focal', '--arch', 'amd64']
    if args.docker:
        make_image_prog += ['--docker']
    elif not args.kvm:
        make_image_prog += ['--lxc', '--disksize', '13000']
    subprocess.check_call(make_image_prog)
    os.chdir(workdir)
    if args.is_focal and not args.kvm and not args.docker:
        subprocess.check_call(['sudo', 'sed', '-i', 's/lxcbr0/br0/', '/etc/default/lxc-net'])
        print('Reboot is required')
        exit(0)

def build():
    global args, workdir

    os.makedirs('whive-binaries/' + args.version, exist_ok=True)
    print('\nBuilding Dependencies\n')
    os.chdir('gitian-builder')
    os.makedirs('inputs', exist_ok=True)

    subprocess.check_call(['wget', '-O', 'inputs/osslsigncode-2.0.tar.gz', 'https://github.com/mtrojnar/osslsigncode/archive/2.0.tar.gz'])
    subprocess.check_call(["echo '5a60e0a4b3e0b4d655317b2f12a810211c50242138322b16e7e01c6fbb89d92f inputs/osslsigncode-2.0.tar.gz' | sha256sum -c"], shell=True)
    subprocess.check_call(['make', '-C', '../bitcoin/depends', 'download', 'SOURCES_PATH=' + os.getcwd() + '/cache/common'])

    if args.linux:
        print('\nCompiling ' + args.version + ' Linux')
        subprocess.check_call(['bin/gbuild', '-j', args.jobs, '-m', args.memory, '--commit', 'whive='+args.commit, '--url', 'whive='+args.url, '../whive/contrib/gitian-descriptors/gitian-linux.yml'])
        subprocess.check_call(['bin/gsign', '-p', args.sign_prog, '--signer', args.signer, '--release', args.version+'-linux', '--destination', '../gitian.sigs/', '../whive/contrib/gitian-descriptors/gitian-linux.yml'])
        subprocess.check_call('mv build/out/whive-*.tar.gz build/out/src/whive-*.tar.gz ../whive-binaries/'+args.version, shell=True)

    if args.windows:
        print('\nCompiling ' + args.version + ' Windows')
        subprocess.check_call(['bin/gbuild', '-j', args.jobs, '-m', args.memory, '--commit', 'whive='+args.commit, '--url', 'whive='+args.url, '../whive/contrib/gitian-descriptors/gitian-win.yml'])
        subprocess.check_call(['bin/gsign', '-p', args.sign_prog, '--signer', args.signer, '--release', args.version+'-win-unsigned', '--destination', '../gitian.sigs/', '../whive/contrib/gitian-descriptors/gitian-win.yml'])
        subprocess.check_call('mv build/out/whive-*-win-unsigned.tar.gz inputs/whive-win-unsigned.tar.gz', shell=True)
        subprocess.check_call('mv build/out/whive-*.zip build/out/whive-*.exe ../whive-binaries/'+args.version, shell=True)

    if args.macos:
        print('\nCompiling ' + args.version + ' MacOS')
        subprocess.check_call(['bin/gbuild', '-j', args.jobs, '-m', args.memory, '--commit', 'whive='+args.commit, '--url', 'whive='+args.url, '../whive/contrib/gitian-descriptors/gitian-osx.yml'])
        subprocess.check_call(['bin/gsign', '-p', args.sign_prog, '--signer', args.signer, '--release', args.version+'-osx-unsigned', '--destination', '../gitian.sigs/', '../whive/contrib/gitian-descriptors/gitian-osx.yml'])
        subprocess.check_call('mv build/out/whive-*-osx-unsigned.tar.gz inputs/whive-osx-unsigned.tar.gz', shell=True)
        subprocess.check_call('mv build/out/whive-*.tar.gz build/out/whive-*.dmg ../whive-binaries/'+args.version, shell=True)

    os.chdir(workdir)

    if args.commit_files:
        print('\nCommitting '+args.version+' Unsigned Sigs\n')
        os.chdir('gitian.sigs')
        subprocess.check_call(['git', 'add', args.version+'-linux/'+args.signer])
        subprocess.check_call(['git', 'add', args.version+'-win-unsigned/'+args.signer])
        subprocess.check_call(['git', 'add', args.version+'-osx-unsigned/'+args.signer])
        subprocess.check_call(['git', 'commit', '-m', 'Add '+args.version+' unsigned sigs for '+args.signer])
        os.chdir(workdir)

def sign():
    global args, workdir
    os.chdir('gitian-builder')

    if args.windows:
        print('\nSigning ' + args.version + ' Windows')
        subprocess.check_call(['bin/gbuild', '-i', '--commit', 'signature='+args.commit, '../whive/contrib/gitian-descriptors/gitian-win-signer.yml'])
        subprocess.check_call(['bin/gsign', '-p', args.sign_prog, '--signer', args.signer, '--release', args.version+'-win-signed', '--destination', '../gitian.sigs/', '../whive/contrib/gitian-descriptors/gitian-win-signer.yml'])
        subprocess.check_call('mv build/out/whive-*win64-setup.exe ../whive-binaries/'+args.version, shell=True)
        subprocess.check_call('mv build/out/whive-*win32-setup.exe ../whive-binaries/'+args.version, shell=True)

    if args.macos:
        print('\nSigning ' + args.version + ' MacOS')
        subprocess.check_call(['bin/gbuild', '-i', '--commit', 'signature='+args.commit, '../whive/contrib/gitian-descriptors/gitian-osx-signer.yml'])
        subprocess.check_call(['bin/gsign', '-p', args.sign_prog, '--signer', args.signer, '--release', args.version+'-osx-signed', '--destination', '../gitian.sigs/', '../whive/contrib/gitian-descriptors/gitian-osx-signer.yml'])
        subprocess.check_call('mv build/out/whive-osx-signed.dmg ../whive-binaries/'+args.version+'/whive-'+args.version+'-osx.dmg', shell=True)

    os.chdir(workdir)

    if args.commit_files:
        print('\nCommitting '+args.version+' Signed Sigs\n')
        os.chdir('gitian.sigs')
        subprocess.check_call(['git', 'add', args.version+'-win-signed/'+args.signer])
        subprocess.check_call(['git', 'add', args.version+'-osx-signed/'+args.signer])
        subprocess.check_call(['git', 'commit', '-a', '-m', 'Add '+args.version+' signed binary sigs for '+args.signer])
        os.chdir(workdir)

def verify():
    global args, workdir
    os.chdir('gitian-builder')

    print('\nVerifying v'+args.version+' Linux\n')
    subprocess.check_call(['bin/gverify', '-v', '-d', '../gitian.sigs/', '-r', args.version+'-linux', '../whive/contrib/gitian-descriptors/gitian-linux.yml'])
    print('\nVerifying v'+args.version+' Windows\n')
    subprocess.check_call(['bin/gverify', '-v', '-d', '../gitian.sigs/', '-r', args.version+'-win-unsigned', '../whive/contrib/gitian-descriptors/gitian-win.yml'])
    print('\nVerifying v'+args.version+' MacOS\n')
    subprocess.check_call(['bin/gverify', '-v', '-d', '../gitian.sigs/', '-r', args.version+'-osx-unsigned', '../whive/contrib/gitian-descriptors/gitian-osx.yml'])
    print('\nVerifying v'+args.version+' Signed Windows\n')
    subprocess.check_call(['bin/gverify', '-v', '-d', '../gitian.sigs/', '-r', args.version+'-win-signed', '../whive/contrib/gitian-descriptors/gitian-win-signer.yml'])
    print('\nVerifying v'+args.version+' Signed MacOS\n')
    subprocess.check_call(['bin/gverify', '-v', '-d', '../gitian.sigs/', '-r', args.version+'-osx-signed', '../whive/contrib/gitian-descriptors/gitian-osx-signer.yml'])

    os.chdir(workdir)

def main():
    global args, workdir

    parser = argparse.ArgumentParser(usage='%(prog)s [options] signer version')
    parser.add_argument('-c', '--commit', action='store_true', dest='commit', help='Indicate that the version argument is for a commit or branch')
    parser.add_argument('-u', '--url', dest='url', default='https://github.com/whiveio/whive', help='Specify the URL of the repository. Default is %(default)s')
    parser.add_argument('-v', '--verify', action='store_true', dest='verify', help='Verify the Gitian build')
    parser.add_argument('-b', '--build', action='store_true', dest='build', help='Do a Gitian build')
    parser.add_argument('-s', '--sign', action='store_true', dest='sign', help='Make signed binaries for Windows and MacOS')
    parser.add_argument('-B', '--buildsign', action='store_true', dest='buildsign', help='Build both signed and unsigned binaries')
    parser.add_argument('-o', '--os', dest='os', default='lwm', help='Specify which Operating Systems the build is for. Default is %(default)s. l for Linux, w for Windows, m for MacOS')
    parser.add_argument('-j', '--jobs', dest='jobs', default='2', help='Number of processes to use. Default %(default)s')
    parser.add_argument('-m', '--memory', dest='memory', default='2000', help='Memory to allocate in MiB. Default %(default)s')
    parser.add_argument('-k', '--kvm', action='store_true', dest='kvm', help='Use KVM instead of LXC')
    parser.add_argument('-d', '--docker', action='store_true', dest='docker', help='Use Docker instead of LXC')
    parser.add_argument('-S', '--setup', action='store_true', dest='setup', help='Set up the Gitian building environment. Uses LXC. If you want to use KVM, use the --kvm option. Only works on Debian-based systems (Ubuntu, Debian)')
    parser.add_argument('-D', '--detach-sign', action='store_true', dest='detach_sign', help='Create the assert file for detached signing. Will not commit anything.')
    parser.add_argument('-n', '--no-commit', action='store_false', dest='commit_files', help='Do not commit anything to git')
    parser.add_argument('signer', help='GPG signer to sign each build assert file')
    parser.add_argument('version', help='Version number, commit, or branch to build. If building a commit or branch, the -c option must be specified')

    args = parser.parse_args()
    workdir = os.getcwd()

    args.is_focal = b'focal' in subprocess.check_output(['lsb_release', '-cs'])

    if args.buildsign:
        args.build=True
        args.sign=True

    if args.kvm and args.docker:
        raise Exception('Error: cannot have both kvm and docker')

    args.sign_prog = 'true' if args.detach_sign else 'gpg --detach-sign'

    # Set enviroment variable USE_LXC or USE_DOCKER, let gitian-builder know that we use lxc or docker
    if args.docker:
        os.environ['USE_DOCKER'] = '1'
    elif not args.kvm:
        os.environ['USE_LXC'] = '1'
        if not 'GITIAN_HOST_IP' in os.environ.keys():
            os.environ['GITIAN_HOST_IP'] = '10.0.3.1'
        if not 'LXC_GUEST_IP' in os.environ.keys():
            os.environ['LXC_GUEST_IP'] = '10.0.3.5'

    # Disable for MacOS if no SDK found
    if args.macos and not os.path.isfile('gitian-builder/inputs/Xcode-12.1-12A7403-extracted-SDK-with-libcxx-headers.tar.gz'):
        print('Cannot build for MacOS, SDK does not exist. Will build for other OSes')
        args.macos = False

    script_name = os.path.basename(sys.argv[0])
    # Signer and version shouldn't be empty
    if args.signer == '':
        print(script_name+': Missing signer.')
        print('Try '+script_name+' --help for more information')
        exit(1)
    if args.version == '':
        print(script_name+': Missing version.')
        print('Try '+script_name+' --help for more information')
        exit(1)

    # Add leading 'v' for tags
    args.commit = ('' if args.commit else 'v') + args.version
    print(args.commit)

    if args.setup:
        setup()

    os.chdir('whive')
    subprocess.check_call(['git', 'fetch'])
    subprocess.check_call(['git', 'checkout', args.commit])
    os.chdir(workdir)

    if args.build:
        build()

    if args.sign:
        sign()

    if args.verify:
        verify()

if __name__ == '__main__':
    main()
