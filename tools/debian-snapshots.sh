#!/bin/bash -e

[ -d src ] || exit 1

# pull last versions
cd trunk-packaging && bzr pull; cd ..
cd trunk-translations && bzr pull; cd ..; ln -sf -t translations trunk-translations/translations/*.po

LASTVERSION=`sed -ne 's/^.*IGOTU_VERSION_STR "\(.*\)"/\1/p' src/lib/igotu/global.h`
FULLVERSION=`sed -n 's/igotu2gpx (\([^-~ )]*\).*/\1/p;T;q' debian/changelog`

echo "last version: $LASTVERSION"
echo "new version: $FULLVERSION (temporary)"

[ -z "`git status --short`" ] || {
    echo "Uncommitted changes, aborting" >&2
    exit 1
}

sed -i 's/\(#define \{1,\}IGOTU_VERSION_STR \).*/\1'"\"$FULLVERSION\"/" src/lib/igotu/global.h
git commit --all --message="bump version to $FULLVERSION when building .deb" --edit

debuild -sa -i -us -uc -b

# cleanup with:
# fakeroot debian/rules clean; rm -rf bin/ tags
