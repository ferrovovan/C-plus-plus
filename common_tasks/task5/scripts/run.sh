#!/usr/bin/bash

echo_green() {
	local text="$1"
	echo -e "\n\033[0;32m$text\033[0m"  # Вывод текста с зелёным цветом
}

echo_green "Тесты"
./build/tests/TimeTests
echo_green "Работа"
./build/main
