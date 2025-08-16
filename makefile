#PREFIX        ?= $(HOME)/.local
PREFIX        ?= /usr/local
BINDIR        := $(PREFIX)/bin
XSESSIONSDIR  := $(PREFIX)/share/xsessions

TARGET          := clips/clips
DESTINATION     := CLIPSX11
TARGET_CLIPSMWM := clipsmwm
SHELL_SCRIPT    := $(TARGET_CLIPSMWM).sh
DESKTOP         := $(TARGET_CLIPSMWM).desktop

DATADIR := $(PREFIX)/share/$(DESTINATION)
DATAFILES := $(wildcard *.clp *.bat)
BAT_TEMPLATE := clipsmwm.bat.in
BAT_OUT := clipsmwm.bat

all: clips
	cp userfunctions.c clips
	$(MAKE) -C clips LDLIBS="-lm -lX11"

clips:
	[ -e clips_core_source_642.tar.gz ] || wget https://sourceforge.net/projects/clipsrules/files/CLIPS/6.4.2/clips_core_source_642.tar.gz
	[ -d "clips" ] || { mkdir clips && tar --strip-components=2 -xvf clips_core_source_642.tar.gz -C clips; }

debug: clips
	cp userfunctions.c clips
	$(MAKE) debug -C clips LDLIBS="-lm -lX11"

install: install-bin install-desktop install-data

install-bin:
	@echo "Installing $(DESTINATION) to $(BINDIR)"
	install -Dm755 $(TARGET) $(BINDIR)/$(DESTINATION)
	@echo "Installing $(SHELL_SCRIPT) to $(BINDIR)"
	install -Dm755 $(SHELL_SCRIPT) $(BINDIR)/$(SHELL_SCRIPT)

install-desktop:
	@echo "Installing $(DESKTOP) to $(XSESSIONSDIR)"
	install -Dm644 $(DESKTOP) $(XSESSIONSDIR)/$(DESKTOP)

install-data:
	@echo "Installing supporting files to $(DATADIR)"
	install -d $(DATADIR)
	install -m644 $(DATAFILES) $(DATADIR)
	sed "s|@DATADIR@|$(DATADIR)|g" $(BAT_TEMPLATE) > $(DATADIR)/$(BAT_OUT)

uninstall:
	@echo "Removing $(BINDIR)/$(DESTINATION)"
	rm -f $(BINDIR)/$(DESTINATION)
	@echo "Removing $(BINDIR)/$(SHELL_SCRIPT)"
	rm -f $(BINDIR)/$(SHELL_SCRIPT)
	@echo "Removing $(XSESSIONSDIR)/$(DESKTOP)"
	rm -f $(XSESSIONSDIR)/$(DESKTOP)
	@echo "Removing $(DATADIR)"
	rm -rf $(DATADIR)

clean:
	$(MAKE) clean -C clips
