DEFAULT_CONFIG_FILE = $(sysconfdir)/GeoIP.conf

GeoIP.conf: GeoIP.conf.default
	@$(SED) -r \
	     -e 's/^(UserId) .*/\1 0/' \
	     -e 's/^(LicenseKey) .*/\1 000000000000/' \
	     -e 's/^(ProductIds .*)\<106 132/\1/' \
	     $^ > $@

install-exec-hook: GeoIP.conf
	@if test -d "$(DESTDIR)$(sysconfdir)" ; then \
		echo "$(MKDIR_P) $(DESTDIR)$(sysconfdir)" ; \
		$(MKDIR_P) "$(DESTDIR)$(sysconfdir)" ; \
	fi
	@if test -f "$(DESTDIR)$(DEFAULT_CONFIG_FILE)" ; then \
	        echo "$@ will not overwrite existing $(DESTDIR)$(DEFAULT_CONFIG_FILE)" ; \
	else \
	        echo "$(INSTALL_DATA) GeoIP.conf $(DESTDIR)$(DEFAULT_CONFIG_FILE)"; \
	        $(INSTALL_DATA) "$(srcdir)/GeoIP.conf" "$(DESTDIR)$(DEFAULT_CONFIG_FILE)"; \
	fi

uninstall-hook:
	@if test -f "$(DESTDIR)$(DEFAULT_CONFIG_FILE)" ; then \
		rm "$(DESTDIR)$(DEFAULT_CONFIG_FILE)"; \
fi
