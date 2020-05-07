NAME = endgame

INC = ./inc/*.h

SRC = ./src/*.c

SDL2 = -I resource/Frameworks/SDL2.framework/Versions/A/Headers -F resource/Frameworks -framework SDL2
SDL2_IMAGE = -I resource/Frameworks/SDL2_image.framework/Versions/A/Headers -F resource/Frameworks/ -framework SDL2_image
SDL2_TTF = -I resource/Frameworks/SDL2_ttf.framework/Versions/A/Headers  -F resource/Frameworks/ -framework SDL2_ttf
SDL2_MIXER = -I resource/Frameworks/SDL2_mixer.framework/Versions/A/Headers  -F resource/Frameworks/ -framework SDL2_mixer

CFLAGS = -std=c11

all: install
install:
	@clang ${CFLAGS} ${SRC} -o ${NAME} ${SDL2} ${SDL2_IMAGE} ${SDL2_TTF} ${SDL2_MIXER} -rpath resource/Frameworks
uninstall: clean
	@rm -rf ${NAME}
clean:

reinstall: uninstall clean all
