CFLAGS += -DPROJECT_CONF_H=\"project-conf.h\"

#linker optimizations
SMALL=1

ifeq ($(APP), sink)

   # Set the project main file
   CONTIKI_PROJECT = $(APP)
   all: $(CONTIKI_PROJECT)

   # Processes path
   PROJECT_SOURCEFILES += udp-server.c rpl-router.c

   # Comment to desable uIPv6
   WITH_UIP6 = 1
   UIP_CONF_IPV6 = 1
   CFLAGS+= -DUIP_CONF_IPV6_RPL
   
endif

ifeq ($(APP), sink.upload)

   # Set the project main file
   CONTIKI_PROJECT = $(APP)
   all: $(CONTIKI_PROJECT)

   # Processes path
   PROJECT_SOURCEFILES += udp-server.c rpl-router.c

   # Comment to desable uIPv6
   WITH_UIP6 = 1
   UIP_CONF_IPV6 = 1
   CFLAGS+= -DUIP_CONF_IPV6_RPL
   
endif

ifeq ($(APP), sensor)

   # Set the project main file
   CONTIKI_PROJECT = $(APP)
   all: $(CONTIKI_PROJECT)

   # Processes path
   PROJECT_SOURCEFILES += udp-client.c sensor_acc.c sensor_hum.c sensor_light.c sensor_temp.c

   # Comment to desable uIPv6
   WITH_UIP6 = 1
   UIP_CONF_IPV6 = 1
   CFLAGS+= -DUIP_CONF_IPV6_RPL
   
endif

ifeq ($(APP), sensor.upload)

   # Set the project main file
   CONTIKI_PROJECT = $(APP)
   all: $(CONTIKI_PROJECT)

   # Processes path
   PROJECT_SOURCEFILES += udp-client.c sensor_acc.c sensor_hum.c sensor_light.c sensor_temp.c

   # Comment to desable uIPv6
   WITH_UIP6 = 1
   UIP_CONF_IPV6 = 1
   CFLAGS+= -DUIP_CONF_IPV6_RPL
   
endif

ifeq ($(APP), udp-server)

   # Set the project main file
   CONTIKI_PROJECT = $(APP)
   all: $(CONTIKI_PROJECT)

   # Processes path
   PROJECT_SOURCEFILES += 

   # Comment to desable uIPv6
   WITH_UIP6 = 1
   UIP_CONF_IPV6 = 1
   CFLAGS+= -DUIP_CONF_IPV6_RPL
   
endif

ifeq ($(APP), udp-client)

   # Set the project main file
   CONTIKI_PROJECT = $(APP)
   all: $(CONTIKI_PROJECT)

   # Processes path
   PROJECT_SOURCEFILES += 

   # Comment to desable uIPv6
   WITH_UIP6 = 1
   UIP_CONF_IPV6 = 1
   CFLAGS+= -DUIP_CONF_IPV6_RPL
   
endif

ifeq ($(APP), rpl-router)

   # Set the project main file
   CONTIKI_PROJECT = $(APP)
   all: $(CONTIKI_PROJECT)

   # Processes path
   PROJECT_SOURCEFILES += 

   # Comment to desable uIPv6
   WITH_UIP6 = 1
   UIP_CONF_IPV6 = 1
   CFLAGS+= -DUIP_CONF_IPV6_RPL
   
endif

# Info
${info CONTIKI_PROJECT = $(PROJECT_PROJECT)}
${info PROJECT_SOURCEFILES = $(PROJECT_SOURCEFILES)}

# Contiki OS path
CONTIKI = ../../contiki
include $(CONTIKI)/Makefile.include

