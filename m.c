#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

#define MAX_STATIONS 41
#define INFINITY (INT_MAX / 2) // Use a large value to represent infinity

void dijkstra(float graph[MAX_STATIONS][MAX_STATIONS], int source, int destination, const char *stations[])
{
    float distances[MAX_STATIONS];
    bool processed[MAX_STATIONS];
    int parent[MAX_STATIONS];

    for (int i = 0; i < MAX_STATIONS; i++)
    {
        distances[i] = INFINITY;
        processed[i] = false;
        parent[i] = -1;
    }

    distances[source] = 0;

    for (int count = 0; count < MAX_STATIONS - 1; count++)
    {
        int u = -1;

        for (int i = 0; i < MAX_STATIONS; i++)
        {
            if (!processed[i] && (u == -1 || distances[i] < distances[u]))
            {
                u = i;
            }
        }

        if (u == -1)
        {
            break;
        }

        processed[u] = true;

        for (int v = 0; v < MAX_STATIONS; v++)
        {
            if (!processed[v] && graph[u][v] > 0 && distances[u] + graph[u][v] < distances[v])
            {
                distances[v] = distances[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    printf("\nShortest Path from %s to %s:\n", stations[source], stations[destination]);
    int p = destination;

    int path[MAX_STATIONS];
    int path_length = 0;

    while (p != source){
       if (path_length >= MAX_STATIONS)
        {
            printf("Error: Path length exceeds maximum stations.\n");
            return;
        }
        
        path[path_length++] = p;
        p = parent[p];
    }

    path[path_length] = source;

    for (int i = path_length; i >= 0; i--)
    {
        printf("%s\n", stations[path[i]]);
    }
    printf("\n");

    float total_distance = distances[destination];

float total_time = 0;
float metro_speed = 30;   
float vehicle_speed = 20; 

for (int i = path_length - 1; i >= 0; i--) 
{
    int current_station = path[i];
    int next_station = path[i - 1];

    if (strstr(stations[current_station], "_Metro_Station") != NULL)
    {
        total_time += (graph[current_station][next_station] / metro_speed) + 0.05;
    }
    else
    {
        total_time += (graph[current_station][next_station] / vehicle_speed)+ 0.05;
    }
}

printf("\nExpected time: %.2f hours\n", total_time);

    printf("Total distance: %.2f km\n", total_distance);

    if (strstr(stations[source], "_Metro_Station") != NULL){
        if (strstr(stations[destination], "_Metro_Station") != NULL){
            printf("Both source and destination are metro stations.\n");
        }
        else{
            printf("Source is a metro station.\n");
            float minDistance = INFINITY;
            int nearestMetroIndex = -1;
            for (int i = 0; i < MAX_STATIONS; i++){
                if (strstr(stations[i], "_Metro_Station") != NULL){
                    if (graph[destination][i] > 0 && graph[destination][i] < minDistance){
                        minDistance = graph[destination][i];
                        nearestMetroIndex = i;
                    }
                }
            }
            printf("Distance from destination to the nearest metro station %s is: %.2f\n", stations[nearestMetroIndex], minDistance);
        }
    }
    else{
        if (strstr(stations[destination], "_Metro_Station") != NULL){
            printf("Destination is a metro station.\n");
            float minDistance = INFINITY;
            int nearestMetroIndex = -1;
            for (int i = 0; i < MAX_STATIONS; i++){
                if (strstr(stations[i], "_Metro_Station") != NULL){
                    if (graph[source][i] > 0 && graph[source][i] < minDistance){
                        minDistance = graph[source][i];
                        nearestMetroIndex = i;
                    }
                }
            }
            printf("Distance from source to the nearest metro station %s is: %.2f\n", stations[nearestMetroIndex], minDistance);
        }
        else{
            printf("Neither source nor destination is a metro station.\n");
        }
    }
}

int find_station_index(const char *station_name, const char *stations[])
{
    for (int i = 0; i < MAX_STATIONS; i++)
    {
        if (strcmp(station_name, stations[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

int main(int argc, char *argv[])
{
    
    float metro_graph[MAX_STATIONS][MAX_STATIONS] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 1.7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 3.7, 0, 0, 0, 0, 0, 2.5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 6.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.4, 0, 0, 0, 0.95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 6.4, 0, 0, 0, 0.8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.75, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.2, 0, 0, 0, 0, 0.95, 0, 0, 3.6, 0, 0, 1.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1.6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.85, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0.65, 0, 0, 0, 0.95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0.95, 0, 0, 0, 0, 0, 1.1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0.9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.9, 0, 0, 0, 0, 0, 3.1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.1, 0, 1.1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0.95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1.2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.8, 1.1, 0, 4.2, 0, 0, 2.1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 1.1, 0.1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0.8, 0, 0, 0, 0, 1.1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0.95, 0, 0, 0, 0, 0, 0, 0, 1.8, 0, 0, 0, 0, 0, 0, 0, 3.6, 0, 0, 1.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1.6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 3.6, 0, 0, 0, 0, 0, 0, 1.7, 4.2, 0, 0, 0, 0, 3.8, 0, 0, 0, 0, 0, 2.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.7, 2.1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1.4, 0, 0, 0, 0, 0, 0, 0, 1.9, 0, 0, 0, 0, 1.6, 0, 0, 2.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0.95, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0.95, 0, 0, 0, 0, 0, 0, 3.1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 8.2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 6.3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.1, 0, 1.1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2.8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3.4, 0, 0, 3.4, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 2, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 2.7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0.45, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 40, 0, 0, 0, 0, 0, 2.9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4.6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.7, 0, 0, 1.7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    };

    const char *stations[MAX_STATIONS] = {
        "Anand_Nagar_Metro_Station", "Bopodi_Metro_Station", "Bund_Garden_Metro_Station",
        "Chhatrapati_Sambhaji_Udyan_Metro_Station", "Civil_Court_Metro_Station",
        "Dapodi_Metro_Station", "Deccan_Gymkhana_Metro_Station", "Garware_College_Metro_Station",
        "Ideal_Colony_Metro_Station", "Kalyani_Nagar_Metro_Station",
        "Kasarwadi_Metro_Station", "Khadki_Metro_Station", "Mangalwar_Peth_Metro_Station",
        "Nal_Stop_Metro_Station", "Nashik_Phata_Metro_Station", "PCMC_Bhavan_Metro_Station",
        "Phugewadi_Metro_Station", "PMC_Bhavan_Metro_Station", "Pune_Railway_Station_Metro_Station",
        "Ramwadi_Metro_Station", "Range_Hills_Metro_Station", "Ruby_Hall_Clinic_Metro_Station", "Sant_Tukaram_Nagar_Metro_Station",
        "Shivaji_Nagar_Metro_Station", "Vanaz_Metro_Station", "Yerwada_Metro_Station", "Katraj", "Bibwewadi", "Shanipar", "Market_yard",
        "swargate", "Gokhalenagar", "camp", "Koregaon_park", "Kothrud", "Karvenagar", "FC_Road",
        "SPPU", "Aundh", "Akurdi", "Wakdewadi"};

    const char *source_station = argv[1];
    const char *destination_station = argv[2];

    int source_index = find_station_index(source_station, stations);
    int destination_index = find_station_index(destination_station, stations);

    if (source_index == -1 || destination_index == -1)
    {
        printf("Error: One or both stations not found.\n");
        return 1;
    }

    dijkstra(metro_graph, source_index, destination_index, stations);

    return 0;
}