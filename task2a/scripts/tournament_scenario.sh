#!/usr/bin/bash

echo_green() {
	local text="$1"
	echo -e "\n\033[0;32m$text\033[0m"  # Вывод текста с зелёным цветом
}

echo_green "Работа \"tournament\""
matrix_dir="./config/matrices/"


Default_matrix=1
if [ $Default_matrix -eq 1 ]; then
	echo_green "Default matrix"
	./build/PrisonersDilemmaSim AlwaysCooperate AlwaysDefect Eye4Eye RandomChoice ConsensusMetaStrategy --mode=tournament
fi

Balanced_Trade_off=0
if [ $Balanced_Trade_off -eq 1 ]; then
	echo_green "Balanced Trade-off"
	matrix="Balanced Trade-off.conf"
	./build/PrisonersDilemmaSim AlwaysCooperate AlwaysDefect Eye4Eye RandomChoice --mode=tournament --matrix="$matrix_dir$matrix"
fi

Extreme_Payoff_for_Solo_Betrayal=0
if [ $Extreme_Payoff_for_Solo_Betrayal -eq 1 ]; then
	echo_green "Extreme Payoff for Solo Betrayal"
	matrix="Extreme Payoff for Solo Betrayal.conf"
	./build/PrisonersDilemmaSim AlwaysCooperate AlwaysDefect Eye4Eye RandomChoice --mode=tournament --matrix="$matrix_dir$matrix"
fi
