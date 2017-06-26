Building igotu2gpx for snap
===========================

About this snap package
-----------------------

This package grows currently to ~90 MB size. I don't have an idea if this is big or small, but I believe it could be optimized to become much smaller.

The package is designed for QT5, thus it can only be used on a branch of igotu2gpx which got already ported from QT4 to QT5 which is not the case on the main branch.

Currently, the snapcraft.yaml has a hard-coded dependency to amd64 (see definition of MARBLE_PLUGIN_PATH). Unfortunately, I didn't find a way to make this more universal.


Building - one of multiple ways (an easy one)
---------------------------------------------

Build:

    docker run -v "$PWD":"$PWD" -w "$PWD" snapcore/snapcraft sh -c "apt-get update && snapcraft"

Clean:

    docker run -v "$PWD":"$PWD" -w "$PWD" snapcore/snapcraft sh -c "snapcraft clean"


Installing on your machine
--------------------------

    sudo snap install --dangerous --devmode igotu2gpx_0.0-test1+git_amd64.snap