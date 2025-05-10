
# ---------------------------------------
#       TIME TRACK TEST
# ---------------------------------------
csv_path="./results/timings.csv"
echo "NUM_TEAMS,MS,NS" > $csv_path
dir="./graphs/var_teams"


while IFS= read -r graph_file; do
  echo "   test for ${graph_file}"
  ./build/ford_fulkerson "1" < "$graph_file"
done < <(find "$dir" -type f)

# ---------------------------------------
#       HEAT MAP TEST
# ---------------------------------------
n=10
c=2
csv_path="./results/heat_map.csv"
echo "A,B,PROB" > $csv_path
for b in  -1 -0.9 -0.8 -0.7 -0.6 -0.5 -0.4 -0.3 -0.2 -0.1 0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1; do
  for a in 0.0 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0; do
    wins=0
    for i in $(seq 1 100); do
      tournament_file=$(mktemp)
      ./build/tournament_gen $n $c $a $b > $tournament_file
      result=$(./build/ford_fulkerson < $tournament_file)

      if [ "$result" = "sim" ]; then
        wins=$((wins + 1))
      fi
      rm $tournament_file
    done
    prob=$(echo "scale=3; $wins / 100" | bc)

    echo "${a},${b},${prob}" >> $csv_path
  done
done