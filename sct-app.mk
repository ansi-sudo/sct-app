SCT_APP_VERSION = 1.0
SCT_APP_SITE = $(BR2_EXTERNAL_NOCTURNE_PATH)/package/sct-app
SCT_APP_SITE_METHOD = local
SCT_APP_DEPENDENCIES = sdl2 sdl2_ttf sdl2_image

define SCT_APP_BUILD_CMDS
	$(MAKE) CC="$(TARGET_CC)" CXX="$(TARGET_CXX)" CFLAGS="$(TARGET_CFLAGS)" \
		LDFLAGS="$(TARGET_LDFLAGS)" -C $(@D)
endef

define SCT_APP_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/sct-app $(TARGET_DIR)/usr/bin/sct-app
	$(INSTALL) -D -m 0755 $(@D)/S99sct-app $(TARGET_DIR)/etc/init.d/S99sct-app
	$(INSTALL) -D -m 0644 $(@D)/splash.png $(TARGET_DIR)/usr/share/sct-app/splash.png
endef

$(eval $(generic-package))