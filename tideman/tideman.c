#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void initialize_disjoint_sets(int parent[], int rank[], int candidate_cnt);
bool union_sets(int parent[], int rank[], int x, int y);
int find(int parent[], int x);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    //loop through candidates array
        //compare candidates[i] with given name
            //if matches
                //insert candidates[i] into ranks[rank]
            //return true
    //end loop
    //return false

    for (int i = 0; i < candidate_count; i++)
    {
        if(strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //loop over ranks using variable i
        //the value of ranks[i] represent the candidate itself
        //the i represents the ranking
        //loop over ranks again using variable j = i + 1
            //ranks[i] is preferred over ranks[j]
            //ranks[j] represents the candidates that ranks[i] is valued over
            //increment preferences[ranks[i]][ranks[j]]
        //end loop when j + 1 < length of ranks is false
    //end loop when i < length of ranks - 1 is false

    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //loop through the amount of candidates with variable i
        //loop through amount of candidates with variable j = i + 1
            //compare preferences[i][j] and preferences[j][i]
                //select the value which is greater
                // if preferences[i][j] > preferences[j][i]
                    //pairs winner = i loser = j
                // else if preferences[i][j] < preferences[j][i]
                    //pairs winner = j loser  = i
            //pairs[pair_count] = pair
            //++pair_count

    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                ++pair_count;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                ++pair_count;
            }

        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    //access the value of the multi-dimensional preferences array using winner and loser of pair
    //strength = preferences[pairs.winner][pairs.loser]
    //sorting can be achieved through insertion sort giving array and size of array
        // loop through the array of pairs using variable i
            //loop through array of pairs again using variable j = i + 1 decrementing j until 0
                //set curr to equal to preferences[pairs[j-1].winner][pairs[j-1].loser]
                //set next = preferences[pairs[j].winner][pairs[j].loser]
                // if next is greater than curr
                    //temp = curr
                    //pairs[i] = next
                    //pairs[j] = temp
                //else
                    //break
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j > 0; j--)
        {
            int curr = preferences[pairs[j-1].winner][pairs[j-1].loser];
            int next = preferences[pairs[j].winner][pairs[j].loser];

            if (next > curr)
            {
               pair temp = pairs[j-1];
               pairs[j-1] = pairs[j];
               pairs[j] = temp;
            }
            else
            {
                break;
            }
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{

    int i_candidates[candidate_count];
    int ranks[candidate_count];
    initialize_disjoint_sets(i_candidates, ranks, candidate_count);


    //Assuming edges is an array of structs {int u, int v, int weight}
    for (int i = 0; i < pair_count; i++) {
        int u = pairs[i].winner;
        int v = pairs[i].loser;

        // Try to union the two candidates
        if (union_sets(i_candidates, ranks, u, v)) {
            // Successfully added the edge to MST
            locked[u][v] = true;
        }
    }

}

// Print the winner of the election
void print_winner(void)
{
    // Iterate Through Candidates:
    //For each candidate i, check if locked[j][i] = 0 for all j (where j ≠ i).
    // Return the Winner: If a candidate meets this condition, they are the winner.

    for (int i = 0; i < candidate_count; i++)
    {
        int found = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (j != i)
            {
                if (locked[j][i] == true)
                {
                    found++;
                }
            }
        }
        if (found == 0)
        {
            printf("%s\n", candidates[i]);
            break;
        }
    }
}


void initialize_disjoint_sets(int parent[], int rank[], int candidate_cnt)
    // iterate for i such that i < candidate_count
        //set parent[i] = i
        //set rank[i] = 0
    // exit loop
{
    for (int i = 0; i < candidate_cnt; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
}

bool union_sets(int parent[], int rank[], int x, int y)
    //set root_x to result of find(parent, x);
    //set root_y to result of find(parent, y);

    //if root_x != root_y
        //attach the smaller tree under the larger tree
        // if rank[root_x] > rank[root_y]
            //attach parent[root_y] = root_x
        //else if rank[root_y] > rank[root_x]
            //attach parent[root_x] = root_y
        //else
            //if ranks are equal, choose one as root and increment its rank
            //parent[root_y] = root_x
            //rank[root_x]++;
{
    int root_x = find(parent, x);
    int root_y = find(parent, y);

    if (root_x != root_y)
    {
        if (rank[root_x] > rank[root_y])
        {
            parent[root_y] = root_x;
        }
        else if (rank[root_y] > rank[root_x])
        {
            parent[root_x] = root_y;
        }
        else
        {
            parent[root_y] = root_x;
            rank[root_x]++;
        }

        return true;
    }
    return false;
}

int find(int parent[], int x)
    //if parent[x] != x
        //set parent[x] to the return value of find giving parent, and parent[x]

    //return parent[x]
{
    if (parent[x] != x)
    {
        parent[x] = find(parent, parent[x]);
    }

    return parent[x];
}

// int find(int parent[], int x)
    //if parent[x] != x
        //set parent[x] to the return value of find giving parent, and parent[x]

    //return parent[x]

//void union_sets(int parent[], int rank[], int x, int y)
    //set root_x to result of find(parent, x);
    //set root_y to result of find(parent, y);

    //if root_x != root_y
        //attach the smaller tree under the larger tree
        // if rank[root_x] > rank[root_y]
            //attach parent[root_y] = root_x
        //else if rank[root_y] > rank[root_x]
            //attach parent[root_x] = root_y
        //else
            //if ranks are equal, choose one as root and increment its rank
            //parent[root_y] = root_x
            //rank[root_x]++;
