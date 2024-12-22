cmake_minimum_required(VERSION 3.20)
project(lab_3)

set(CMAKE_CXX_STANDARD 23)
set(SFML_DIR "C:/SFML/lib/cmake/SFML")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

include_directories("C:/SFML/include")
link_directories("C:/SFML/lib")

add_executable(lab_3 main.cpp
        ISortedSequence.h
        IDictionary.h
        menu.h
        Tests/Summary_Tests.h
        Tests/Tests_IDictionary.h
        Tests/Tests_ISortedSequence.h
        HashTable.h
        RedBlackTree.h
        TicTacToe/GameLogic.h
        TicTacToe/AIEngine.h
        TicTacToe/GraphicsElements.h
        TicTacToe/GameWindow.h
        ExamplesOfClasses/DictionaryApp.cpp
        ExamplesOfClasses/DictionaryApp.h
        ExamplesOfClasses/MainMenu.cpp
        ExamplesOfClasses/MainMenu.h
        ExamplesOfClasses/SortedSequenceApp.cpp
        ExamplesOfClasses/SortedSequenceApp.h
        StyleSheetUtils.h)

target_link_libraries(lab_3 PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
