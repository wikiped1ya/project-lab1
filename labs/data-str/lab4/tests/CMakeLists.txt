# Создаём исполняемый файл для теста
add_executable(test_simple test_simple.cpp)

# Добавляем тест в CTest
add_test(NAME SimpleTest COMMAND test_simple)
