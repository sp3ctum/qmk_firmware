# https://docs.qmk.fm/install-build-tools#docker
# You'll run this every time you want to build a keymap
# modify the keymap and keyboard assignment to compile what you want
# defaults are ergodox/default

# docker run -e keymap=mika -e keyboard=ergodox_ez --rm -v $('pwd'):/qmk:rw edasque/qmk_firmware
./util/docker_build.sh ergodox_ez:mika
