<h2 align="center"><i>DWM</i></h2>

<p align="center">
<img src="https://img.shields.io/github/workflow/status/toalaah/dwm/Build?color=pink&logo=github&style=for-the-badge"
     alt="build status" />
<img src="https://img.shields.io/github/license/toalaah/dwm?color=add8e6&style=for-the-badge"
     alt="build status" />
<br><br>
This repo contains my personal <a href="https://tools.suckless.org/dwm">dwm</a>
fork. The original repo can be found <a href="https://git.suckless.org/dwm">here</a>.

## Features

- Customizable gap/window settings per workspace
- Xresources compatibility
- Hot-reloading via <kbd>Super</kbd>+<kbd>Shift</kbd>+<kbd>r</kbd>
- Native support of most EWMH hints:
    ```
    _NET_SUPPORTED(ATOM) = _NET_SUPPORTED, _NET_WM_NAME, _NET_WM_STATE, _NET_SUPPORTING_WM_CHECK, _NET_WM_STATE_FULLSCREEN, _NET_WM_DESKTOP, _NET_ACTIVE_WINDOW, _NET_WM_WINDOW_TYPE, _NET_WM_WINDOW_TYPE_DIALOG, _NET_CLIENT_LIST, _NET_DESKTOP_NAMES, _NET_DESKTOP_VIEWPORT, _NET_NUMBER_OF_DESKTOPS, _NET_CURRENT_DESKTOP
    ```
- Support for external status-bars (this build uses Polybar by default)
- True fullscreen mode <kbd>Super</kbd>+<kbd>Shift</kbd>+<kbd>f</kbd>
- Window-swallow support (spawned children processes consume parent window for
  specified process classes)

## Installation

1. Make sure you have the required Xlib headers installed. By default, Polybar
   is used as a status bar, although DWM will still run without it being
   installed. Then, simply clone the repository and run the following make
   commands:

   ```bash
   # optional, can also opt into builtin bar in by disabling `usealtbar` in `config.h`
   sudo pacman -S polybar
   git clone git@github.com:Toalaah/dwm.git ~/.config/dwm
   cd ~/.config/dwm
   make
   sudo make install
   ```

## Patches

> All patches can be found in the [patches](./patches) folder.

Most patches were installed by hand, so there may not be a one-to-one
correspondence between the diff and source files. They are mainly stored in
the repository for future reference.

### Applied Patches:

- [shiftview](https://lists.suckless.org/dev/1104/7590.html)
- [attachaside](https://dwm.suckless.org/patches/attachaside/)
- [pertag](https://dwm.suckless.org/patches/pertag/)
- [xresources](https://dwm.suckless.org/patches/xresources/)
- [swallow](https://dwm.suckless.org/patches/swallow/)
- [functionalgaps](https://dwm.suckless.org/patches/functionalgaps/)
- [anybar](https://dwm.suckless.org/patches/anybar/)
- [ewmhtags](https://dwm.suckless.org/patches/ewmhtags/)
- [actualfullscreen](https://dwm.suckless.org/patches/actualfullscreen/)
- [alwayscenter](https://dwm.suckless.org/patches/alwayscenter/)
- [restartsig](https://dwm.suckless.org/patches/restartsig/)

## License

[MIT](./LICENSE)
