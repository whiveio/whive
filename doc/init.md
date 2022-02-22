Sample init scripts and service configuration for whived
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/whived.service:    systemd service unit configuration
    contrib/init/whived.openrc:     OpenRC compatible SysV style init script
    contrib/init/whived.openrcconf: OpenRC conf.d file
    contrib/init/whived.conf:       Upstart service configuration file
    contrib/init/whived.init:       CentOS compatible SysV style init script

Service User
---------------------------------

All three Linux startup configurations assume the existence of a "Whive" user
and group.  They must be created before attempting to use these scripts.
The macOS configuration assumes whived will be set up for the current user.

Configuration
---------------------------------

Running whived as a daemon does not require any manual configuration. You may
set the `rpcauth` setting in the `whive.conf` configuration file to override
the default behaviour of using a special cookie for authentication.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that whived and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If whived is run with the "-server" flag (set by default), and no rpcpassword is set,
it will use a special cookie file for authentication. The cookie is generated with random
content when the daemon starts, and deleted when it exits. Read access to this file
controls who can access it through RPC.

By default the cookie is stored in the data directory, but it's location can be overridden
with the option '-rpccookiefile'.

This allows for running whived without having to do any manual configuration.

`conf`, `pid`, and `wallet` accept relative paths which are interpreted as
relative to the data directory. `wallet` *only* supports relative paths.

For an example configuration file that describes the configuration settings,
see `share/examples/whive.conf`.

Paths
---------------------------------

### Linux

All three configurations assume several paths that might need to be adjusted.

Binary:              `/usr/bin/whived`
Configuration file:  `/etc/whive/whive.conf`
Data directory:      `/var/lib/whived`
PID file:            `/var/run/whived/whived.pid` (OpenRC and
Upstart) or 
                     `/run/whived/whived.pid` (systemd)
Lock file:           `/var/lock/subsys/whived` (CentOS)

The PID directory (if applicable) and data directory should both be owned by the
whive user and group. It is advised for security reasons to make the
configuration file and data directory only readable by the whive user and
group. Access to whive-cli and other whived rpc clients can then be
controlled by group membership.

### macOS

Binary:              `/usr/local/bin/whived`  
Configuration file:  `~/Library/Application Support/Whive/whive.conf`  
Data directory:      `~/Library/Application Support/Whive`  
Lock file:           `~/Library/Application Support/Whive/.lock`  

Installing Service Configuration
-----------------------------------

### systemd

Installing this .service file consists of just copying it to
/usr/lib/systemd/system directory, followed by the command
`systemctl daemon-reload` in order to update running systemd configuration.

To test, run `systemctl start whived` and to enable for system startup run
`systemctl enable whived`

NOTE: When installing for systemd in Debian/Ubuntu the .service file needs to be copied to the /lib/systemd/system directory instead.

### OpenRC

Rename whived.openrc to whived and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
`/etc/init.d/whived start` and configure it to run on startup with
`rc-update add whived`

### Upstart (for Debian/Ubuntu based distributions)

Upstart is the default init system for Debian/Ubuntu versions older than 15.04. If you are using version 15.04 or newer and haven't manually configured upstart you should follow the systemd instructions instead.

Drop whived.conf in /etc/init.  Test by running `service whived start`
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon utility.

### CentOS

Copy whived.init to /etc/init.d/whived. Test by running `service whived start`.

Using this script, you can adjust the path and flags to the whived program by
setting the BITCOIND and FLAGS environment variables in the file
/etc/sysconfig/whived. You can also use the DAEMONOPTS environment variable here.

### macOS

Copy org.whive.whived.plist into ~/Library/LaunchAgents. Load the launch agent by
running `launchctl load ~/Library/LaunchAgents/org.whive.whived.plist`.

This Launch Agent will cause whived to start whenever the user logs in.

NOTE: This approach is intended for those wanting to run whived as the current user.
You will need to modify org.whive.whived.plist if you intend to use it as a
Launch Daemon with a dedicated whive user.

Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
