# README

My build of dwm

Status bar: dwm_status_kai.sh

Human-readable list of patches: https://github.com/bakkeby/dwm-flexipatch

| markdown | table |
remove attachbottom, apply attachdirection
remove switchtotag (and extra column), apply focusurgent

## Patches I use
* attachbottom		-- less obtrusive window spawning; troublesome when you actually want the master (e.g. opening pdfs/images)
* bottomstack		-- for work with long lines of text
* centeredmaster	-- i don't use this much tbh
* cool-autostart	-- control autostart via config.h
* deck			-- for latex work
* hide_vacant_tags	-- i3-like
* losefullscreen	-- disable true fs (not monocle) when focus changes
* sendmon_keepfocus	-- auto-focus window on new monitor
* shiftviewclients	-- cycle through tags (skip empty ones)
* switchtotag		-- auto-focus window on new tag (need extra window prop); mainly for vbox
* warp			-- move cursor when focus changes

## Patches I might use
* actualfullscreen / togglefullscreen
* attachdirection (above/aside/below/top)
* ewmhtags / focusonnetactive	-- allow wmctrl
* focusurgent		-- simpler than switchtotag?
* inplacerotate / movestack / rotatestack
* monoclesymbol		-- use actual symbol
* nametag		-- change tag name while running
* onlyquitonempty	-- don't kill dwm if windows remain
* pertag		-- tag-specific layouts
* push_no_master	-- easier than movestack
* regex-rules		-- more flexible window-matching; messy
* restartsig / selfrestart	-- auto-restart dwm
* swapfocus / switchcol / focusmaster	-- zoom without changing position
* windowrolerule	-- will this help with deeznuts?
* zoomswap		-- 'weakens' zoom (swap master with stack, instead of pushing to 2)

## Patches I no longer/probably won't use
* centeredwindowname	-- not practical with long status bar; maybe with taller bar
* dwmblocks
* fakefullscreen	-- i usually want actual fullscreen
* focusadjacenttag	-- 'unclean' patch; use shiftviewclients instead
* scratchpad
* swallow		-- i prefer floating
* systray		-- bloat
