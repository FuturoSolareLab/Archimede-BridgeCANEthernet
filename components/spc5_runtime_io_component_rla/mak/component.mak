##############################################################################
# References to the component library (./component/lib) locations.

LIB_C_SRC       += \
	./components/spc5_runtime_io_component_rla/lib/src/close.c \
	./components/spc5_runtime_io_component_rla/lib/src/fstat.c \
	./components/spc5_runtime_io_component_rla/lib/src/isatty.c \
	./components/spc5_runtime_io_component_rla/lib/src/lseek.c \
	./components/spc5_runtime_io_component_rla/lib/src/open.c \
	./components/spc5_runtime_io_component_rla/lib/src/read.c \
	./components/spc5_runtime_io_component_rla/lib/src/sbrk.c \
	./components/spc5_runtime_io_component_rla/lib/src/spc5_io.c \
	./components/spc5_runtime_io_component_rla/lib/src/write.c


LIB_CPP_SRC     +=

LIB_ASM_SRC     +=

LIB_INCLUDES    += \
	./components/spc5_runtime_io_component_rla/lib/include

##############################################################################
# References to the application locations.

APP_C_SRC       += ./components/spc5_runtime_io_component_rla/cfg/spc5_io_cfg.c \

APP_CPP_SRC     +=

APP_ASM_SRC     +=

APP_INCLUDES    += ./components/spc5_runtime_io_component_rla/cfg

##############################################################################
# Default directories, definitions and libraries.

# C/C++ definitions (-D....).
DDEFS   +=

# Assembled definitions (-D....).
DADEFS  +=

# Include files search directories separated by spaces.
DINCDIR +=

# Library files search directories separated by spaces.
DLIBDIR +=

# Libraries (-l...).
DLIBS   +=
