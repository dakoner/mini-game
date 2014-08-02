LOADLIBES=-lBox2D -L/home/dek/Qt/5.3/gcc_64/lib -lQt5Core -lQt5Widgets -lQt5Gui
CXXFLAGS=-I/home/dek/Qt/5.3/gcc_64/include -pipe -std=c++11 -O2 -Wall -W -D_REENTRANT -fPIE -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB

moc_%.cpp: %.h
	/home/dek/Qt/5.3/gcc_64/bin/moc $(DEFINES) $(INCPATH) $< -o $@

test: test.cpp box2dengine.cpp box2dengine.h moc_box2dengine.cpp MotionFilter.h moc_MotionFilter.cpp UpdateReceiver.h moc_UpdateReceiver.cpp

clean:
	rm -f moc_box2dengine.cpp moc_MotionFilter.cpp moc_UpdateReceiver.cpp