if g++ -c -O3 -funroll-loops core.cpp; then
	echo -e "Compiling Core...			\E[32m[DONE]\E[37m"
else
	echo -e "Compiling Core...			\E[31m[ERROR]\E[37m"
	exit
fi

if g++ -c -O3 -funroll-loops arm7.cpp; then
	echo -e "Compiling ARMv7...			\E[32m[DONE]\E[37m"
else
	echo -e "Compiling ARMv7...			\E[31m[ERROR]\E[37m"
	exit
fi

if g++ -c -O3 -funroll-loops dma.cpp; then
	echo -e "Compiling DMA...			\E[32m[DONE]\E[37m"
else
	echo -e "Compiling DMA...			\E[31m[ERROR]\E[37m"
	exit
fi

if g++ -c -O3 -funroll-loops arm_instr.cpp; then
	echo -e "Compiling ARM instructions...		\E[32m[DONE]\E[37m"
else
	echo -e "Compiling ARM instructions...		\E[31m[ERROR]\E[37m"
	exit
fi

if g++ -c -O3 -funroll-loops thumb_instr.cpp; then
	echo -e "Compiling THUMB instructions...		\E[32m[DONE]\E[37m"
else
	echo -e "Compiling THUMB instructions...		\E[31m[ERROR]\E[37m"
	exit
fi

if g++ -c -O3 -funroll-loops swi.cpp; then
	echo -e "Compiling SWI...			\E[32m[DONE]\E[37m"
else
	echo -e "Compiling SWI...			\E[31m[ERROR]\E[37m"
	exit
fi

if g++ -c -O3 -funroll-loops mmu.cpp; then
	echo -e "Compiling MMU...			\E[32m[DONE]\E[37m"
else
	echo -e "Compiling MMU...			\E[31m[ERROR]\E[37m"
	exit
fi

if g++ -c -O3 -funroll-loops lcd.cpp -lSDL; then
	echo -e "Compiling LCD...			\E[32m[DONE]\E[37m"
else
	echo -e "Compiling LCD...			\E[31m[ERROR]\E[37m"
	exit
fi

if g++ -c -O3 -funroll-loops apu.cpp -lSDL; then
	echo -e "Compiling APU...			\E[32m[DONE]\E[37m"
else
	echo -e "Compiling APU...			\E[31m[ERROR]\E[37m"
	exit
fi

if g++ -c -O3 -funroll-loops opengl.cpp -lSDL -lGL; then
	echo -e "Compiling OpenGL...			\E[32m[DONE]\E[37m"
else
	echo -e "Compiling OpenGL...			\E[31m[ERROR]\E[37m"
	exit
fi

if g++ -c -O3 -funroll-loops gamepad.cpp -lSDL; then
	echo -e "Compiling Gamepad...			\E[32m[DONE]\E[37m"
else
	echo -e "Compiling Gamepad...			\E[31m[ERROR]\E[37m"
	exit
fi


if g++ -c -O3 -funroll-loops config.cpp -lSDL; then
	echo -e "Compiling Config...			\E[32m[DONE]\E[37m"
else
	echo -e "Compiling Config...			\E[31m[ERROR]\E[37m"
	exit
fi


if g++ -c -O3 -funroll-loops main.cpp; then
	echo -e "Compiling Main...			\E[32m[DONE]\E[37m"
else
	echo -e "Compiling Main...			\E[31m[ERROR]\E[37m"
	exit
fi

if g++ -o gbe_plus core.o arm7.o dma.o arm_instr.o thumb_instr.o swi.o mmu.o gamepad.o lcd.o apu.o opengl.o config.o main.o -lSDL -lGL; then
	echo -e "Linking Project...			\E[32m[DONE]\E[37m"
else
	echo -e "Linking Project...			\E[31m[ERROR]\E[37m"
	exit
fi