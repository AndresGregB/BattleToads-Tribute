INC := `sdl2-config --cflags`
INC += -I.

LIB := `sdl2-config --libs`
LIB += -lSDL2 -lSDL2_image -lSDL2_mixer 

CC := g++
CFLAGS := 

UNAME := $(shell uname)

ifeq ($(UNAME),Darvin)
	CC=clang++
else
	CC=g++
endif

clean:
	cd BattleToads && \
	rm -f *.o *~ Main

compile:
	cd BattleToads && \
	$(CC) $(CFLAGS) -g *.cpp $(INC) $(LIB) -o Main 	

run:
	cd BattleToads && \
	./Main 	

format:
	find BattleToads -name '*.cpp' -exec indent {} \;
	find BattleToads -name '*.h' -exec indent {} \;

docker-build:
	docker build . -t sdl-compiler

docker-compile:	docker-build
	docker run -v $(PWD):/home/docker -ti sdl-compiler make compile

args = `arg="$(filter-out $@,$(MAKECMDGOALS))" && echo $${arg:-${1}}`
docker-run:
	docker run --net host \
	-e DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix:ro \
	-v "$(PWD):/home/docker" \
	sdl-compiler \
	$(args)

docker-mac-run:
	docker run --net host -e DISPLAY=docker.for.mac.host.internal:0 \
	-v "$(PWD):/home/docker" \
	sdl-compiler \
	$(args)
