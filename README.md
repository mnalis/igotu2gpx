This is fork of launchpad version, prepared so it works on Debian Stable with latest patches

- get latest upstream from https://launchpad.net/igotu2gpx
- add debian/* from upstream with "bzr branch lp:~igotu2gpx/igotu2gpx/trunk-packaging/"
- add patches from launchpad (GT-200e better clear support, fix 2016+ dates etc. - see github log)

Use tools/debian-snapshots.sh to create debian package
