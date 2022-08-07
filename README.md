# README

My build of dwm

Status bar: dwm_status_kai.sh

Human-readable list of patches: https://github.com/bakkeby/dwm-flexipatch

| markdown | table |
https://github.com/bakkeby/patches/wiki/switchtag
remove? deck

## Patches I use

- attachbottom -- less obtrusive window spawning; extra keypress when you actually want the master (e.g. zathura, sxiv, lynxreader)
- cool-autostart -- control autostart via config.h
- deck -- for latex work
- hide_vacant_tags -- i3-like
- losefullscreen -- disable true fs (not monocle) when focus changes
- push_no_master -- move windows up/down the stack; does not allow pushing to master
- restartsig -- auto-restart dwm; all windows get moved to tag 1; may bork status bar font
- shiftviewclients -- cycle through tags (skip empty ones)
- singularborders -- remove outer borders, merge inner borders; borders have some inherent latency
- switchtag -- auto-focus window on new tag (need extra window prop)

## Patches I might use

- actualfullscreen / togglefullscreen
- ewmhtags -- allow wmctrl
- keychord -- keybinds without needing to hold a key
- nametag -- change tag name while running
- onlyquitonempty -- don't kill dwm if windows remain
- pertag -- tag-specific layouts
- regex-rules -- more flexible window-matching; unclean patch
- swapfocus / switchcol / focusmaster -- zoom without changing position
- windowrolerule -- will this help with deeznuts?
- zoomswap -- 'weakens' zoom (swap master with stack, instead of pushing to 2)

## Patches I no longer/probably won't use

- attachdirection (above/aside/below/top) -- bottom is fine with me
- bottomstack
- centeredmaster
- centeredwindowname -- not practical with long status bar; maybe with taller bar
- dwmblocks
- fakefullscreen -- i usually want actual fullscreen
- focusadjacenttag -- 'unclean' patch; use shiftviewclients instead
- focusonnetactive -- idk what this does
- focusurgent -- doesn't work
- inplacerotate / movestack / rotatestack -- same as push_no_master
- monoclesymbol -- use actual symbol
- scratchpad
- sendmon_keepfocus -- auto-focus window when moved to new monitor; but not newly spawned window!
- swallow -- i prefer floating
- switchtotag -- "switch back to previous tag" behaviour is very annoying!
- systray -- bloat
- warp -- move cursor when focus changes; more annoying than useful
