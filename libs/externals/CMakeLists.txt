include_directories(
   ${CMAKE_CURRENT_SOURCE_DIR}
   ${CMAKE_CURRENT_SOURCE_DIR}/..
   )

# next target: dbus interfaces library
set(knmconnection_SRCS
    connectable.cpp
    interfaceconnection.cpp
    wirelessinterfaceconnection.cpp
    wirelessnetworkitem.cpp
    )

qt4_add_dbus_adaptor(
    knmconnection_SRCS
    interfaces/org.kde.networkmanagement.connectable.xml
    connectable.h
    Knm::Externals::Connectable
)

qt4_add_dbus_adaptor(
    knmconnection_SRCS
    interfaces/org.kde.networkmanagement.interfaceconnection.xml
    interfaceconnection.h
    Knm::Externals::InterfaceConnection
)

qt4_add_dbus_adaptor(
    knmconnection_SRCS
    interfaces/org.kde.networkmanagement.wirelessinterfaceconnection.xml
    wirelessinterfaceconnection.h
    Knm::Externals::WirelessInterfaceConnection
)

qt4_add_dbus_adaptor(
    knmconnection_SRCS
    interfaces/org.kde.networkmanagement.wirelessnetworkitem.xml
    wirelessnetworkitem.h
    Knm::Externals::WirelessNetworkItem
)

kde4_add_library(
    knmexternals SHARED ${knmconnection_SRCS}
)

target_link_libraries(knmexternals ${KDE4_KDECORE_LIBS} solidcontrol)

set_target_properties(knmexternals PROPERTIES
   VERSION ${GENERIC_LIB_VERSION}
   SOVERSION ${GENERIC_LIB_SOVERSION}
   )

install(TARGETS knmexternals ${INSTALL_TARGETS_DEFAULT_ARGS})

