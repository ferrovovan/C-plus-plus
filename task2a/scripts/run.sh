#!/usr/bin/bash

echo_green() {
	local text="$1"
	echo -e "\n\033[0;32m$text\033[0m"  # Вывод текста с зелёным цветом
}

echo_green "Работа"

# fast
./build/PrisonersDilemmaSim AlwaysCooperate AlwaysDefect Eye4Eye --mode=fast --steps=10 --matrix=./config/default_matrix.conf

# tournament
./build/PrisonersDilemmaSim AlwaysCooperate AlwaysDefect Eye4Eye RandomChoice --mode=tournament --matrix=./config/default_matrix.conf