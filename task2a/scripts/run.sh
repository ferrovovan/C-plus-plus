#!/usr/bin/bash

echo_green() {
	local text="$1"
	echo -e "\n\033[0;32m$text\033[0m"  # Вывод текста с зелёным цветом
}

echo_green "Работа"
matrix_dir="./config/matrices/"

echo_green "Balanced Trade-off"
matrix="Balanced Trade-off.conf"
# fast
./build/PrisonersDilemmaSim AlwaysCooperate AlwaysDefect Eye4Eye --mode=fast --steps=10 --matrix="$matrix_dir$matrix"

# tournament
./build/PrisonersDilemmaSim AlwaysCooperate AlwaysDefect Eye4Eye RandomChoice --mode=tournament --matrix="$matrix_dir$matrix"

echo_green "Extreme Payoff for Solo Betrayal"
matrix="Extreme Payoff for Solo Betrayal.conf"
# fast
./build/PrisonersDilemmaSim AlwaysCooperate AlwaysDefect Eye4Eye --mode=fast --steps=10 --matrix="$matrix_dir$matrix"

# tournament
./build/PrisonersDilemmaSim AlwaysCooperate AlwaysDefect Eye4Eye RandomChoice --mode=tournament --matrix="$matrix_dir$matrix"