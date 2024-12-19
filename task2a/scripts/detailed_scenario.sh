#!/usr/bin/bash

echo_green() {
	local text="$1"
	echo -e "\n\033[0;32m$text\033[0m"  # Вывод текста с зелёным цветом
}

echo_green "Работа \"detailed\""
matrix_dir="./config/matrices/"


Default_matrix=1
if [ $Default_matrix -eq 1 ]; then
	echo_green "Default matrix"
	./build/PrisonersDilemmaSim AlwaysCooperate AlwaysDefect Eye4Eye --mode=detailed --steps=10
fi

Balanced_Trade_off=0
if [ $Balanced_Trade_off -eq 1 ]; then
	echo_green "Balanced Trade-off"
	matrix="Balanced Trade-off.conf"
	./build/PrisonersDilemmaSim AlwaysCooperate AlwaysDefect Eye4Eye --mode=detailed --steps=10 --matrix="$matrix_dir$matrix"
fi
