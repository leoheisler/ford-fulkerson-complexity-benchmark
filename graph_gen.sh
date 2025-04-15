echo "creating 15 mesh graphs"
echo "for checking limit in iterations"
graph_prefix="graphs/mesh_graphs/"
funct=1

max_col=180
min_col=80
max_row=180
min_row=80
max_C=1000
min_C=100
# r, c  max = 180
# r, c  min = 80
# vertex_max = rc + 2 => 32.840
# vertex_min = rc + 2 => 6.402
# edges_max = 2r + 3(c - 1)r => 97.020
# edges_min = 2r + 3(c - 1)r => 19.120 
for i in {1..15}; do
    col=$((RANDOM % (max_col - min_col + 1) + min_col))
    row=$((RANDOM % (max_row - min_row + 1) + min_row))
    C=$((RANDOM % (max_C - min_C + 1) + min_C))


    graph_name="${graph_prefix}${col}_${row}_${C}.gr"
    echo "creating graph col:${col}_row: ${row} graph_C: ${C}"

    ./build/graph_gen "$funct" "$row" "$col" "$C" "$graph_name"

    sleep 1
done


echo "creating 15 line graphs"
echo "for checking limit in iterations"
graph_prefix="graphs/line_graphs/"
funct=6

max_col=100
min_col=50
max_row=100
min_row=50
max_C=500
min_C=50
max_d=5
min_d=1

# n, m  max = 100
# n, m  min = 50
# vertex_max = n * m + 2 => 10.002
# vertex_min = n * m + 2 => 2.502
# edges_max = n * m * d + 2 * m => 50.200
# edges_min = n * m * d + 2 * m => 2.600

for i in {1..15}; do
    col=$((RANDOM % (max_col - min_col + 1) + min_col))
    row=$((RANDOM % (max_row - min_row + 1) + min_row))
    C=$((RANDOM % (max_C - min_C + 1) + min_C))
    d=$((RANDOM % (max_d - min_d + 1) + min_d))

    graph_name="${graph_prefix}${col}_${row}_${C}.gr"
    echo "creating graph col:${col}_row:${row}_graph_C:${C}_graph_d:${d}"

    ./build/graph_gen "$funct" "$row" "$col" "$C" "$d" "$graph_name"

    sleep 1
done


echo "creating 15 rand2 graphs"
echo "for checking limit in iterations"
graph_prefix="graphs/rand2_graphs/"
funct=3

max_col=180
min_col=80
max_row=180
min_row=80
max_C=1000
min_C=100
# r, c  max = 180
# r, c  min = 80
# vertex_max = rc + 2 => 32.840
# vertex_min = rc + 2 => 6.402
# edges_max = 2r + 3(c - 1)r => 97.020
# edges_min = 2r + 3(c - 1)r => 19.120 
for i in {1..15}; do
    col=$((RANDOM % (max_col - min_col + 1) + min_col))
    row=$((RANDOM % (max_row - min_row + 1) + min_row))
    C=$((RANDOM % (max_C - min_C + 1) + min_C))


    graph_name="${graph_prefix}${col}_${row}_${C}.gr"
    echo "creating graph col:${col}_row: ${row} graph_C: ${C}"

    ./build/graph_gen "$funct" "$row" "$col" "$C" "$graph_name"

    sleep 1
done


#creating ordered 
