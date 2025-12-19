#!/bin/bash


if [ $# -eq 0 ]; then
    echo "Ошибка: передайте числа в качестве аргументов"
    exit 1
fi


numbers=("$@")


calculate_average() {
    local arr=("$@")
    local sum=0

    for num in "${arr[@]}"; do
        sum=$((sum + num))
    done

    average=$(echo "scale=2; $sum / ${#arr[@]}" | bc)
    echo "$average"
}


result=$(calculate_average "${numbers[@]}")

echo "Среднее значение: $result"
