#!/usr/bin/env bash
# Copyright (c) 2018-2019 The Bitcoin Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

# Assert expected shebang lines

export LC_ALL=C
EXIT_CODE=0
for PYTHON_FILE in $(git ls-files -- "*.py"); do
    if [[ $(head -c 2 "${PYTHON_FILE}") == "#!" &&
          $(head -n 1 "${PYTHON_FILE}") != "#!/usr/bin/env python3" ]]; then
        echo "Missing shebang \"#!/usr/bin/env python3\" in ${PYTHON_FILE} (do not use python or python2)"
        EXIT_CODE=1
    fi
done
exit ${EXIT_CODE}
