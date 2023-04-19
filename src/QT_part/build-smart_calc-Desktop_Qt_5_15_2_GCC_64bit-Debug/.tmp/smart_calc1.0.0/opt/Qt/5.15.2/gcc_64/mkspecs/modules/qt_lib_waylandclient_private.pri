QT.waylandclient_private.VERSION = 5.15.2
QT.waylandclient_private.name = QtWaylandClient
QT.waylandclient_private.module =
QT.waylandclient_private.libs = $$QT_MODULE_LIB_BASE
QT.waylandclient_private.includes = $$QT_MODULE_INCLUDE_BASE/QtWaylandClient/5.15.2 $$QT_MODULE_INCLUDE_BASE/QtWaylandClient/5.15.2/QtWaylandClient
QT.waylandclient_private.frameworks =
QT.waylandclient_private.depends = core_private gui_private waylandclient service_support_private xkbcommon_support_private
QT.waylandclient_private.uses =
QT.waylandclient_private.module_config = v2 internal_module
QT.waylandclient_private.enabled_features = wayland-client egl-extension-platform-wayland wayland-client-fullscreen-shell-v1 wayland-client-ivi-shell wayland-client-primary-selection wayland-client-wl-shell wayland-client-xdg-shell wayland-client-xdg-shell-v5 wayland-client-xdg-shell-v6 wayland-datadevice wayland-dmabuf-server-buffer wayland-drm-egl-server-buffer wayland-egl wayland-shm-emulation-server-buffer wayland-vulkan-server-buffer xcomposite-egl xcomposite-glx
QT.waylandclient_private.disabled_features = wayland-brcm wayland-libhybris-egl-server-buffer
QMAKE_DEPENDS_WAYLAND_CURSOR_CC = WAYLAND_CLIENT
QMAKE_DEPENDS_WAYLAND_CURSOR_LD = WAYLAND_CLIENT
QMAKE_INCDIR_GLX = /usr/include/libdrm
QMAKE_LIBS_WAYLAND_CLIENT = -lwayland-client
QMAKE_LIBS_WAYLAND_CURSOR = -lwayland-cursor
QMAKE_LIBS_WAYLAND_EGL = -lwayland-egl -lwayland-client
QMAKE_LIBS_XCOMPOSITE = -lXcomposite
QMAKE_LIBS_GLX = -lX11 -lGL
