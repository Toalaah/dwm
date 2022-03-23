### Personal dwm (dynamic window manager) fork

The original repo can be found [here](https://git.suckless.org/dwm)

### Applied Patches

- [Shiftview](https://lists.suckless.org/dev/1104/7590.html), for rotating tags more efficiently.
- [Pertag](https://dwm.suckless.org/patches/pertag/), allows for custom gap widths, client sizes, etc. on a per-workspace basis.
- [Functionalgaps](https://dwm.suckless.org/patches/functionalgaps/), for enabling gaps.
- [Xresources](https://dwm.suckless.org/patches/xresources/), for interacting / reading colors and variables from my xresources file.
- [Always-centered](https://dwm.suckless.org/patches/alwayscenter/), for always ensuring all floating windows are centered.
- [Centered-Master](https://dwm.suckless.org/patches/centeredmaster/), alternative layout in which the master window is centered instead of off to the side.
- [Hide vacant tags](https://dwm.suckless.org/patches/hide_vacant_tags/), for only showing workspaces in the statusbar which have actual content.
- [Underline tags](https://dwm.suckless.org/patches/hide_vacant_tags/), slight aesthetic change to statusbar which underlines the current workspace you are on (with some modifications by myself to make toggling the functionality of the patch more accessible).
- Custom "non-vacant-tag-highlight" patch, changes the default highlight given to non-empty workspaces to a sleeker rectangle which, in my opinion, looks better. Can be customized in a similar fashion to the `underline tags` patch by modifying `config.h`.
- [Attatchaside](https://dwm.suckless.org/patches/attachaside/), changes how windows are spawned.
- [Title-Color](https://dwm.suckless.org/patches/titlecolor/), allows you to define a colorscheme specific to the title-section of the bar.
- Custom "hide-titles" patch, allows you to specify whether the title of the currently selected window is shown in the bar. Can be toggled by changing the variable `showtitles` in `config.h`
- [Swallow](https://dwm.suckless.org/patches/swallow/), Makes terminal which spawns new window-processes "consume" the process, replacing the terminal until it is exited, restoring the original terminal.
- [Alternative tags](https://dwm.suckless.org/patches/alternativetags/), allow hotswapping between two sets of tag-indicators.
- [Scratchpad](https://dwm.suckless.org/patches/namedscratchpads/), Allows for the creation of multiple scratchpad windows.
- [Actualfullscreen](https://dwm.suckless.org/patches/actualfullscreen/), Better fullscreen experience
