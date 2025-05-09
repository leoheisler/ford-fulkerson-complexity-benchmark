tournament_prefix="graphs/"

echo "creating 25 var tournaments"
instance="${tournament_prefix}var_teams"
mkdir -p "$instance" 

num_equipes=20
rounds=5
for i in {1..25}; do
  tournament_name="/${i}_${num_equipes}.txt"
  ./build/tournament_gen  "$num_equipes" "$rounds" >> "${instance}${tournament_name}"
  ((num_equipes+=10))
done