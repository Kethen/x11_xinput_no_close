### x11_xinput_no_close

Workaround for https://bugs.winehq.org/show_bug.cgi?id=59772 , tested on 11.9 staging

```
# build the workaround
bash build.sh
# wine-staging, loading the workaround while making sure that the x11 driver is used so that drawing tablet works as of 11.9
WAYLAND_DISPLAY="" LD_PRELOAD="$(pwd)/x11_xinput_no_close.so" wine your_art_program.exe
```
