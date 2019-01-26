// 1 - Top
// 2 - Front
// 3 - Right
// 4 - Back
// 5 - Left
// 6 - Bottom
int compare(short int i1, short int j1, short int k1, short int pos1, short int i2, short int j2, short int k2, short int pos2)
{
	return *((short int*) &cube[i1][j1][k1] + pos1) == *((short int*) &cube[i2][j2][k2] + pos2);
}

int search(int option, short int i1, short int j1, short int k1, short int pos1, short int i2, short int j2, short int k2, short int pos2, short int i3, short int j3, short int k3, short int pos3)
{
	// option:
	// 0 for edge
	// 1 for corner
	int i, k, found;
	if (!option)
	{
		for (i = 0; i < 12; i++)
		{
			found = 0;
			for (k = 1; k < 7; k++)
				if ((compare(edge[i][0], edge[i][1], edge[i][2], k, i1, j1, k1, pos1)) || (compare(edge[i][0], edge[i][1], edge[i][2], k, i2, j2, k2, pos2)))
					found++;
			if (found == 2)
				return i;
		}
	}
	
	else
	{
		for (i = 0; i < 8; i++)
		{
			found = 0;
			for (k = 1; k < 7; k++)
				if ((compare(corners[i][0], corners[i][1], corners[i][2], k, i1, j1, k1, pos1)) || (compare(corners[i][0], corners[i][1], corners[i][2], k, i2, j2, k2, pos2)) || (compare(corners[i][0], corners[i][1], corners[i][2], k, i3, j3, k3, pos3)))
					found++;
			if (found == 3)
				return i;
		}
	}
	return -1; // impossible
}

int first_layer_cross_solved()
{
	int count = 0, i;
	for (i = 0; i < 4; i++)
		if (compare(edge[i][0], edge[i][1], edge[i][2], 6, 2, 1, 1, 6))
			count++;
	if (count == 4)
		return 1;
	return 0;
}

int first_layer_corners_solved()
{
	int count = 0, i;
	for (i = 0; i < 4; i++)
		if (compare(corners[i][0], corners[i][1], corners[i][2], 6, 2, 1, 1, 6))
			count++;
	if ((count == 4) && (compare(corners[0][0], corners[0][1], corners[0][2], 2, 2, 2, 1, 2) && compare(corners[0][0], corners[0][1], corners[0][2], 3, 2, 1, 2, 3) && compare(corners[1][0], corners[1][1], corners[1][2], 3, 2, 1, 2, 3) && compare(corners[1][0], corners[1][1], corners[1][2], 4, 2, 0, 1, 4) && compare(corners[2][0], corners[2][1], corners[2][2], 4, 2, 0, 1, 4) && compare(corners[2][0], corners[2][1], corners[2][2], 5, 2, 1, 0, 5) && compare(corners[3][0], corners[3][1], corners[3][2], 5, 2, 1, 0, 5) && compare(corners[3][0], corners[3][1], corners[3][2], 2, 2, 2, 1, 2)))
		return 1;
	return 0;
}

int second_layer_edges_solved()
{
	if (compare(edge[4][0], edge[4][1], edge[4][2], 2, 1, 2, 1, 2) && compare(edge[4][0], edge[4][1], edge[4][2], 3, 1, 1, 2, 3) && compare(edge[5][0], edge[5][1], edge[5][2], 3, 1, 1, 2, 3) && compare(edge[5][0], edge[5][1], edge[5][2], 4, 1, 0, 1, 4) && compare(edge[6][0], edge[6][1], edge[6][2], 4, 1, 0, 1, 4) && compare(edge[6][0], edge[6][1], edge[6][2], 5, 1, 1, 0, 5) && compare(edge[7][0], edge[7][1], edge[7][2], 5, 1, 1, 0, 5) && compare(edge[7][0], edge[7][1], edge[7][2], 2, 1, 2, 1, 2))
		return 1;
	return 0;
}

int cross_last_layer_solved()
{
	int count = 0, i;
	for (i = 8; i < 12; i++)
		if (compare(edge[i][0], edge[i][1], edge[i][2], 1, 0, 1, 1, 1))
			count++;
	if (count == 4)
		return 1;
	return 0;
}

int last_layer_up_solved()
{
	int count = 0, i;
	for (i = 4; i < 8; i++)
		if (compare(corners[i][0], corners[i][1], corners[i][2], 1, 0, 1, 1, 1))
			count++;
	if (count == 4)
		return 1;
	return 0;
}

int pll_solved()
{
	if (compare(corners[4][0], corners[4][1], corners[4][2], 2, 0, 2, 1, 2) && compare(corners[4][0], corners[4][1], corners[4][2], 3, 0, 1, 2, 3) && compare(corners[5][0], corners[5][1], corners[5][2], 3, 0, 1, 2, 3) && compare(corners[5][0], corners[5][1], corners[5][2], 4, 0, 0, 1, 4) && compare(corners[6][0], corners[6][1], corners[6][2], 4, 0, 0, 1, 4) && compare(corners[6][0], corners[6][1], corners[6][2], 5, 0, 1, 0, 5) && compare(corners[7][0], corners[7][1], corners[7][2], 5, 0, 1, 0, 5) && compare(corners[7][0], corners[7][1], corners[7][2], 2, 0, 2, 1, 2))
		return 1;
	return 0;
}

void first_layer_cross()
{
	int i, found;
	// First layer cross
	if (first_layer_cross_solved())
		return;
	for (i = 0; i < 4; i++)
	{
		found = search(0, 2, 1, 1, 6, 1, 2, 1, 2, 0, 0, 0, 0);
		if (edge[found][0] == 2)
		{
			if ((edge[found][1] == 2) && (edge[found][2] == 1))
			{
				if (!compare(edge[found][0], edge[found][1], edge[found][2], 6, 2, 1, 1, 6))
					split("F D' L D");
			}
					
			else if ((edge[found][1] == 1) && (edge[found][2] == 2))
			{
				if (compare(edge[found][0], edge[found][1], edge[found][2], 6, 2, 1, 1, 6))
					split("R D R' D'");
				else
					split("R F");
			}	
			else if ((edge[found][1] == 0) && (edge[found][2] == 1))
			{
				if (compare(edge[found][0], edge[found][1], edge[found][2], 6, 2, 1, 1, 6))
					split("B2 U2 F2");
				else
					split("B R' U R F2");
			}	
			else if ((edge[found][1] == 1) && (edge[found][2] == 0))
			{
				if (compare(edge[found][0], edge[found][1], edge[found][2], 6, 2, 1, 1, 6))
					split("L' D' L D");
				else
					split("L' F'");
			}
		}
		else if (edge[found][0] == 1)
		{
			if ((edge[found][1] == 2) && (edge[found][2] == 2))
			{
				if (compare(edge[found][0], edge[found][1], edge[found][2], 3, 2, 1, 1, 6))
					split("F");
				else
					split("D R' D'");
			}	
			else if ((edge[found][1] == 0) && (edge[found][2] == 2))
			{
				if (compare(edge[found][0], edge[found][1], edge[found][2], 3, 2, 1, 1, 6))
					split("B U B' U F2");
				else
					split("R' U R F2");
			}		
			else if ((edge[found][1] == 0) && (edge[found][2] == 0))
			{
				if (compare(edge[found][0], edge[found][1], edge[found][2], 5, 2, 1, 1, 6))
					split("B' U' B U' F2");
				else
					split("L U' L' F2");
			}	
			else if ((edge[found][1] == 2) && (edge[found][2] == 0))
			{
				if (compare(edge[found][0], edge[found][1], edge[found][2], 5, 2, 1, 1, 6))
					split("F'");
				else
					split("D' L D");
			}
		}
		else if (!edge[found][0])
		{
			if ((edge[found][1] == 2) && (edge[found][2] == 1))
			{
				if (compare(edge[found][0], edge[found][1], edge[found][2], 1, 2, 1, 1, 6))
					split("F2");
				else
					split("F D R' D'");
			}
			else if ((edge[found][1] == 1) && (edge[found][2] == 2))
			{
				if (compare(edge[found][0], edge[found][1], edge[found][2], 1, 2, 1, 1, 6))
					split("U F2");
				else
					split("R' F R");
			}	
			else if ((edge[found][1] == 0) && (edge[found][2] == 1))
			{
				if (compare(edge[found][0], edge[found][1], edge[found][2], 1, 2, 1, 1, 6))
					split("U2 F2");
				else
					split("U R' F R");
			}	
			else if ((edge[found][1] == 1) && (edge[found][2] == 0))
			{
				if (compare(edge[found][0], edge[found][1], edge[found][2], 1, 2, 1, 1, 6))
					split("U' F2");
				else
					split("L F' L'");
			}
		}	
		split("Y");
		print_cube();
	}
}

void first_layer_corners()
{
	int i, found;
	// First Layer Corners
	if (first_layer_corners_solved())
		return;
	for (i = 0; i < 4; i++)
	{
		found = search(1, 2, 1, 1, 6, 1, 2, 1, 2, 1, 1, 2, 3);
		if (corners[found][0] == 2)
		{
			if ((corners[found][1] == 2) && (corners[found][2] == 2))
			{
				if (compare(corners[found][0], corners[found][1], corners[found][2], 3, 2, 1, 1, 6))
					split("R U R' U' R U R'");
				else if (compare(corners[found][0], corners[found][1], corners[found][2], 2, 2, 1, 1, 6))
					split("F' U' F U F' U' F");
			}
					
			else if ((corners[found][1] == 0) && (corners[found][2] == 2))
			{
				if (compare(corners[found][0], corners[found][1], corners[found][2], 6, 2, 1, 1, 6))
					split("B U B' F' U' F");
				else if (compare(corners[found][0], corners[found][1], corners[found][2], 4, 2, 1, 1, 6))
					split("B U B' R U R'");
				else
					split("B U B' R U2 R' U' R U R'");
			}	
			else if ((corners[found][1] == 0) && (corners[found][2] == 0))
			{
				if (compare(corners[found][0], corners[found][1], corners[found][2], 6, 2, 1, 1, 6))
					split("B' U' B U' R U R'");
				else if (compare(corners[found][0], corners[found][1], corners[found][2], 5, 2, 1, 1, 6))
					split("B' U' B U' R U2 R' U' R U R'");
				else
					split("B' U' B U' F' U' F");
			}
			else if ((corners[found][1] == 2) && (corners[found][2] == 0))
			{
				if (compare(corners[found][0], corners[found][1], corners[found][2], 6, 2, 1, 1, 6))
					split("L' U' L R U R'");
				else if (compare(corners[found][0], corners[found][1], corners[found][2], 2, 2, 1, 1, 6))
					split("L' U' L R U2 R' U' R U R'");
				else
					split("L' U' L F' U' F");
			}
		}
		
		else if (!corners[found][0])
		{
			if ((corners[found][1] == 2) && (corners[found][2] == 2))
			{
				if (compare(corners[found][0], corners[found][1], corners[found][2], 2, 2, 1, 1, 6))
					split("F' U' F");
				else if (compare(corners[found][0], corners[found][1], corners[found][2], 3, 2, 1, 1, 6))
					split("R U R'");
				else
					split("R U2 R' U' R U R'");
			}
			else if ((corners[found][1] == 0) && (corners[found][2] == 2))
			{
				if (compare(corners[found][0], corners[found][1], corners[found][2], 3, 2, 1, 1, 6))
					split("U F' U' F");
				else if (compare(corners[found][0], corners[found][1], corners[found][2], 4, 2, 1, 1, 6))
					split("U R U R'");
				else
					split("U R U2 R' U' R U R'");
			}
			else if ((corners[found][1] == 0) && (corners[found][2] == 0))
			{
				if (compare(corners[found][0], corners[found][1], corners[found][2], 4, 2, 1, 1, 6))
					split("U2 F' U' F");
				else  if (compare(corners[found][0], corners[found][1], corners[found][2], 5, 2, 1, 1, 6))
					split("U2 R U R'");
				else
					split("U2 R U2 R' U' R U R'");
			}
			else if ((corners[found][1] == 2) && (corners[found][2] == 0))
			{
				if (compare(corners[found][0], corners[found][1], corners[found][2], 5, 2, 1, 1, 6))
					split("U' F' U' F");
				else if (compare(corners[found][0], corners[found][1], corners[found][2], 2, 2, 1, 1, 6))
					split("U' R U R'");
				else
					split("U' R U2 R' U' R U R'");
			}		
		}
		split("Y");
		print_cube();
	}
}

void second_layer_edges()
{
	int i, found;
	// Second Layer edges
	if (second_layer_edges_solved())
		return;
	for (i = 0; i < 4; i++)
	{
		found = search(0, 1, 2, 1, 2, 1, 1, 2, 3, 0, 0, 0, 0);
		if (edge[found][0])
		{
			if ((edge[found][1] == 2) && (edge[found][2] == 2))
			{
				if (compare(edge[found][0], edge[found][1], edge[found][2], 3, 1, 2, 1, 2))
					split("R U' R' U F' U2 F U2 F' U F");
			}
			else if ((edge[found][1] == 0) && (edge[found][2] == 2))
			{
				if (compare(edge[found][0], edge[found][1], edge[found][2], 4, 1, 2, 1, 2))
					split("B U B' U' R' U' R2 U' R' U' F' U F");
				else
					split("B U B' U' R' U' R U2 R U' R' U' R U' R' U R U R'");
			}
			else if ((edge[found][1] == 0) && (edge[found][2] == 0))
			{
				if (compare(edge[found][0], edge[found][1], edge[found][2], 5, 1, 2, 1, 2))
					split("B' U' B U L U L' R U' R' U' R U' R' U R U R'");
				else
					split("B' U' B U L U L' U2 R U' R' U' F' U F");
			}	
			else if ((edge[found][1] == 2) && (edge[found][2] == 0))
			{
				if (compare(edge[found][0], edge[found][1], edge[found][2], 2, 1, 2, 1, 2))
					split("L' U' L U F U F' U R U' R' U' R U' R' U R U R'");
				else
					split("L' U' L U F U F' U' R U' R' U' F' U F");
			}
		}
		
		else if (!edge[found][0])
		{
			if ((edge[found][1] == 2) && (edge[found][2] == 1))
			{
				if (compare(edge[found][0], edge[found][1], edge[found][2], 2, 1, 2, 1, 2))
					split("U R U' R' U' F' U F");
				else
					split("U' R U' R' U' R U' R' U R U R'");
			}	
			else if ((edge[found][1] == 1) && (edge[found][2] == 2))
			{
				if (compare(edge[found][0], edge[found][1], edge[found][2], 3, 1, 2, 1, 2))
					split("U2 R U' R' U' F' U F");
				else
					split("R U' R' U' R U' R' U R U R'");
			}
			else if ((edge[found][1] == 0) && (edge[found][2] == 1))
			{
				if (compare(edge[found][0], edge[found][1], edge[found][2], 4, 1, 2, 1, 2))
					split("U' R U' R' U' F' U F");
				else
					split("U R U' R' U' R U' R' U R U R'");
			}	
			else if ((edge[found][1] == 1) && (edge[found][2] == 0))
			{
				if (compare(edge[found][0], edge[found][1], edge[found][2], 5, 1, 2, 1, 2))
					split("R U' R' U' F' U F");
				else
					split("U2 R U' R' U' R U' R' U R U R'");
			}
		}
		split("Y");
		print_cube();
	}
}

void cross_last_layer()
{
	int i;
	// Cross Last Layer
	if (cross_last_layer_solved())
		return;
	if (!(compare(0, 0, 1, 1, 0, 1, 1, 1) && compare(0, 1, 0, 1, 0, 1, 1, 1) && compare(0, 1, 2, 1, 0, 1, 1, 1) && compare(0, 2, 1, 1, 0, 1, 1, 1)))
	{
		if (!compare(0, 0, 1, 1, 0, 1, 1, 1) && !compare(0, 1, 0, 1, 0, 1, 1, 1) && !compare(0, 1, 2, 1, 0, 1, 1, 1) && !compare(0, 2, 1, 1, 0, 1, 1, 1))
			split("R U2 R2 F R F' U2 R' F R F'");
		else
		{
			for (i = 0; i < 4; i++)
			{
				if (compare(0, 0, 1, 1, 0, 1, 1, 1) && compare(0, 1, 0, 1, 0, 1, 1, 1))
				{
					split("F U R U' R' F'");
					break;
				}
				else if (compare(0, 1, 0, 1, 0, 1, 1, 1) && compare(0, 1, 2, 1, 0, 1, 1, 1))
				{
					split("F R U R' U' F'");
					break;
				}
				split("U");
				print_cube();
			}
		}
	}
}

void last_layer_up()
{
	int i;
	// Last Layer Up
	if (last_layer_up_solved())
		return;
	for (i = 0; i < 4; i++)
	{
		if (compare(0, 2, 2, 2, 0, 1, 1, 1) && compare(0, 0, 2, 3, 0, 1, 1, 1) && compare(0, 0, 0, 4, 0, 1, 1, 1) && compare(0, 2, 0, 1, 0, 1, 1, 1))
		{
			split("R U R' U R U2 R'");
			break;
		}
		else if (compare(0, 2, 2, 3, 0, 1, 1, 1) && compare(0, 0, 2, 1, 0, 1, 1, 1) && compare(0, 0, 0, 5, 0, 1, 1, 1) && compare(0, 2, 0, 2, 0, 1, 1, 1))
		{
			split("R U2 R' U' R U' R'");
			break;
		}
		else if (compare(0, 2, 2, 3, 0, 1, 1, 1) && compare(0, 0, 2, 3, 0, 1, 1, 1) && compare(0, 0, 0, 5, 0, 1, 1, 1) && compare(0, 2, 0, 5, 0, 1, 1, 1))
		{
			split("R U R' U R U' R' U R U2 R'");
			break;
		}
		else if (compare(0, 2, 2, 2, 0, 1, 1, 1) && compare(0, 0, 2, 4, 0, 1, 1, 1) && compare(0, 0, 0, 5, 0, 1, 1, 1) && compare(0, 2, 0, 5, 0, 1, 1, 1))
		{
			split("R U2 R2 U' R2 U' R2 U2 R");
			break;
		}
		else if (compare(0, 2, 2, 2, 0, 1, 1, 1) && compare(0, 0, 2, 4, 0, 1, 1, 1) && compare(0, 0, 0, 1, 0, 1, 1, 1) && compare(0, 2, 0, 1, 0, 1, 1, 1))
		{
			split("R' F' L F R F' L' F");
			break;
		}
		else if (compare(0, 2, 2, 1, 0, 1, 1, 1) && compare(0, 0, 2, 4, 0, 1, 1, 1) && compare(0, 0, 0, 1, 0, 1, 1, 1) && compare(0, 2, 0, 5, 0, 1, 1, 1))
		{
			split("R' F' L' F R F' L F");
			break;
		}
		else if (compare(0, 2, 2, 2, 0, 1, 1, 1) && compare(0, 0, 2, 1, 0, 1, 1, 1) && compare(0, 0, 0, 1, 0, 1, 1, 1) && compare(0, 2, 0, 2, 0, 1, 1, 1)) 
		{
			split("R2 D R' U2 R D' R' U2 R'");
			break;
		}
		split("U");
		print_cube();
	}
}

void pll()
{
	int i;
	// PLL -> Permutate Last Layer (edges and corners)
	if (!pll_solved())
	{	
		for (i = 0; i < 4; i++)
		{
			if (compare(0, 2, 0, 2, 0, 2, 1, 2) && compare(0, 2, 1, 2, 0, 2, 2, 2) && compare(0, 0, 0, 4, 0, 0, 1, 4) && compare(0, 0, 1, 4, 0, 0, 2, 4) && compare(0, 0, 0, 5, 0, 1, 0, 5) && compare(0, 1, 0, 5, 0, 2, 0, 5) && compare(0, 0, 2, 3, 0, 1, 2, 3) && compare(0, 1, 2, 3, 0, 2, 2, 3))
				break;
				
			if (compare(0, 0, 0, 5, 0, 0, 1, 4) && compare(0, 0, 0, 4, 0, 0, 2, 4) && compare(0, 0, 0, 4, 0, 1, 2, 3) && compare(0, 0, 0, 5, 0, 2, 2, 2) && compare(0, 0, 1, 4, 0, 2, 2, 2) && compare(0, 0, 2, 4, 0, 1, 2, 3) && compare(0, 0, 2, 3, 0, 2, 0, 2) && compare(0, 0, 2, 3, 0, 2, 1, 2) && compare(0, 1, 0, 5, 0, 2, 0, 5) && compare(0, 1, 0, 5, 0, 2, 2, 3) && compare(0, 2, 0, 2, 0, 2, 1, 2) && compare(0, 2, 0, 5, 0, 2, 2, 3))
			{
				split("R' F R' B2 R F' R' B2 R2"); // Aa
				break;
			}
			
			else if (compare(0, 0, 0, 5, 0, 1, 2, 3) && compare(0, 0, 0, 4, 0, 2, 0, 2) && compare(0, 0, 0, 4, 0, 2, 1, 2) && compare(0, 0, 0, 5, 0, 2, 2, 2) && compare(0, 0, 1, 4, 0, 0, 2, 3) && compare(0, 0, 1, 4, 0, 2, 2, 3) && compare(0, 0, 2, 4, 0, 1, 0, 5) && compare(0, 0, 2, 4, 0, 2, 0, 5) && compare(0, 0, 2, 3, 0, 2, 2, 3) && compare(0, 1, 0, 5, 0, 2, 0, 5) && compare(0, 1, 2, 3, 0, 2, 2, 2) && compare(0, 2, 0, 2, 0, 2, 1, 2))
			{
				split("R2 B2 R F R' B2 R F' R"); // Ab
				break;
			}
			
			else if (compare(0, 0, 0, 5, 0, 0, 2, 3) && compare(0, 0, 0, 4, 0, 1, 0, 5) && compare(0, 0, 0, 4, 0, 2, 0, 2) && compare(0, 0, 0, 5, 0, 2, 1, 2) && compare(0, 0, 1, 4, 0, 2, 0, 5) && compare(0, 0, 1, 4, 0, 2, 2, 3) && compare(0, 0, 2, 4, 0, 1, 2, 3) && compare(0, 0, 2, 3, 0, 2, 1, 2) && compare(0, 0, 2, 4, 0, 2, 2, 2) && compare(0, 1, 0, 5, 0, 2, 0, 2) && compare(0, 1, 2, 3, 0, 2, 2, 2) && compare(0, 2, 0, 5, 0, 2, 2, 3))
			{
				split("R B' R' F R B R' F' R B R' F R B' R' F'"); // E
				break;
			}
			
			else if (compare(0, 0, 0, 4, 0, 0, 1, 4) && compare(0, 0, 0, 4, 0, 0, 2, 4) && compare(0, 0, 0, 5, 0, 1, 2, 3) && compare(0, 0, 0, 5, 0, 2, 0, 5) && compare(0, 0, 1, 4, 0, 0, 2, 4) && compare(0, 0, 2, 3, 0, 2, 1, 2) && compare(0, 0, 2, 3, 0, 2, 2, 3) && compare(0, 1, 0, 5, 0, 2, 0, 2) && compare(0, 1, 0, 5, 0, 2, 2, 2) && compare(0, 1, 2, 3, 0, 2, 0, 5) && compare(0, 2, 0, 2, 0, 2, 2, 2) && compare(0, 2, 1, 2, 0, 2, 2, 3))
			{
				split("R U' R U R U R U' R' U' R2"); // Ua
				break;
			}
			
			else if (compare(0, 0, 0, 4, 0, 0, 1, 4) && compare(0, 0, 0, 4, 0, 0, 2, 4) && compare(0, 0, 0, 5, 0, 2, 0, 5) && compare(0, 0, 0, 5, 0, 2, 1, 2) && compare(0, 0, 1, 4, 0, 0, 2, 4) && compare(0, 0, 2, 3, 0, 1, 0, 5) && compare(0, 0, 2, 3, 0, 2, 2, 3) && compare(0, 1, 0, 5, 0, 2, 2, 3) && compare(0, 1, 2, 3, 0, 2, 0, 2) && compare(0, 1, 2, 3, 0, 2, 2, 2) && compare(0, 2, 0, 5, 0, 2, 1, 2) && compare(0, 2, 0, 2, 0, 2, 2, 2))
			{
				split("R2 U R U R' U' R' U' R' U R'"); // Ub
				break;
			}
			
			else if (compare(0, 0, 0, 4, 0, 0, 2, 4) && compare(0, 0, 0, 5, 0, 1, 2, 3) && compare(0, 0, 0, 5, 0, 2, 0, 5) && compare(0, 0, 0, 4, 0, 2, 1, 2) && compare(0, 0, 1, 4, 0, 2, 0, 2) && compare(0, 0, 1, 4, 0, 2, 2, 2) && compare(0, 0, 2, 3, 0, 1, 0, 5) && compare(0, 0, 2, 4, 0, 2, 1, 2) && compare(0, 0, 2, 3, 0, 2, 2, 3) && compare(0, 1, 0, 5, 0, 2, 2, 3) && compare(0, 1, 2, 3, 0, 2, 0, 5) && compare(0, 2, 0, 2, 0, 2, 2, 2))
			{
				split("R2 L2 D' R2 L2 U2 R2 L2 D' R2 L2"); // H
				break;
			}
			
			else if (compare(0, 0, 0, 5, 0, 0, 1, 4) && compare(0, 0, 0, 4, 0, 0, 2, 4) && compare(0, 0, 0, 4, 0, 1, 0, 5) && compare(0, 0, 0, 5, 0, 2, 0, 5) && compare(0, 0, 1, 4, 0, 2, 0, 5) && compare(0, 0, 2, 4, 0, 1, 0, 5) && compare(0, 0, 2, 3, 0, 2, 1, 2) && compare(0, 0, 2, 3, 0, 2, 2, 3) && compare(0, 1, 2, 3, 0, 2, 0, 2) && compare(0, 1, 2, 3, 0, 2, 2, 2) && compare(0, 2, 0, 2, 0, 2, 2, 2) && compare(0, 2, 1, 2, 0, 2, 2, 3))
			{
				split("U R' U' R U' R U R U' R' U R U R2 U' R' U"); // Z
				break;
			}
			
			else if (compare(0, 0, 0, 5, 0, 0, 2, 3) && compare(0, 0, 0, 5, 0, 1, 0, 5) && compare(0, 0, 0, 4, 0, 1, 2, 3) && compare(0, 0, 0, 4, 0, 2, 2, 3) && compare(0, 0, 1, 4, 0, 0, 2, 4) && compare(0, 0, 1, 4, 0, 2, 0, 5) && compare(0, 0, 2, 3, 0, 1, 0, 5) && compare(0, 0, 2, 4, 0, 2, 0, 5) && compare(0, 1, 2, 3, 0, 2, 2, 3) && compare(0, 2, 0, 2, 0, 2, 1, 2) && compare(0, 2, 0, 2, 0, 2, 2, 2) && compare(0, 2, 1, 2, 0, 2, 2, 2))
			{
				split("R' U L' U2 R U' R' U2 L R U'"); // Ja
				break;
			}
			
			else if (compare(0, 0, 0, 4, 0, 0, 1, 4) && compare(0, 0, 0, 5, 0, 1, 0, 5) && compare(0, 0, 0, 5, 0, 2, 0, 5) && compare(0, 0, 0, 4, 0, 2, 2, 3) && compare(0, 0, 1, 4, 0, 2, 2, 3) && compare(0, 0, 2, 3, 0, 1, 2, 3) && compare(0, 0, 2, 3, 0, 2, 0, 2) && compare(0, 0, 2, 4, 0, 2, 1, 2) && compare(0, 0, 2, 4, 0, 2, 2, 2) && compare(0, 1, 0, 5, 0, 2, 0, 5) && compare(0, 1, 2, 3, 0, 2, 0, 2) && compare(0, 2, 1, 2, 0, 2, 2, 2))
			{
				split("R U R' F' R U R' U' R' F R2 U' R' U'"); // Jb
				break;
			}
			
			else if (compare(0, 0, 0, 4, 0, 0, 1, 4) && compare(0, 0, 0, 5, 0, 1, 2, 3) && compare(0, 0, 0, 5, 0, 2, 0, 5) && compare(0, 0, 0, 4, 0, 2, 2, 3) && compare(0, 0, 1, 4, 0, 2, 2, 3) && compare(0, 0, 2, 4, 0, 1, 0, 5) && compare(0, 0, 2, 3, 0, 2, 0, 2) && compare(0, 0, 2, 3, 0, 2, 1, 2) && compare(0, 0, 2, 4, 0, 2, 2, 2) && compare(0, 1, 0, 5, 0, 2, 2, 2) && compare(0, 1, 2, 3, 0, 2, 0, 5) && compare(0, 2, 0, 2, 0, 2, 1, 2))
			{
				split("R U R' U' R' F R2 U' R' U' R U R' F'"); // T
				break;
			}
			
			else if (compare(0, 0, 0, 5, 0, 0, 1, 4) && compare(0, 0, 0, 4, 0, 1, 0, 5) && compare(0, 0, 0, 5, 0, 2, 0, 5) && compare(0, 0, 0, 4, 0, 2, 2, 3) && compare(0, 0, 1, 4, 0, 2, 0, 5) && compare(0, 0, 2, 4, 0, 1, 2, 3) && compare(0, 0, 2, 3, 0, 2, 0, 2) && compare(0, 0, 2, 3, 0, 2, 1, 2) && compare(0, 0, 2, 4, 0, 2, 2, 2) && compare(0, 1, 0, 5, 0, 2, 2, 3) && compare(0, 1, 2, 3, 0, 2, 2, 2) && compare(0, 2, 0, 2, 0, 2, 1, 2))
			{
				split("R U R' F' R U2 R' U2 R' F R U R U2 R' U'"); // Ra
				break;
			}
			
			else if (compare(0, 0, 0, 5, 0, 0, 1, 4) && compare(0, 0, 0, 5, 0, 0, 2, 3) && compare(0, 0, 0, 4, 0, 2, 1, 2) && compare(0, 0, 0, 4, 0, 2, 2, 3) && compare(0, 0, 1, 4, 0, 0, 2, 3) && compare(0, 0, 2, 4, 0, 1, 0, 5) && compare(0, 0, 2, 4, 0, 2, 0, 5) && compare(0, 1, 0, 5, 0, 2, 0, 5) && compare(0, 1, 2, 3, 0, 2, 0, 2) && compare(0, 1, 2, 3, 0, 2, 2, 2) && compare(0, 2, 0, 2, 0, 2, 2, 2) && compare(0, 2, 1, 2, 0, 2, 2, 3))
			{
				split("R' U2 R U2 R' F R U R' U' R' F' R2 U'"); // Rb
				break;
			}
			
			else if (compare(0, 0, 0, 5, 0, 1, 0, 5) && compare(0, 0, 0, 5, 0, 2, 0, 5) && compare(0, 0, 0, 4, 0, 2, 1, 2) && compare(0, 0, 0, 4, 0, 2, 2, 3) && compare(0, 0, 1, 4, 0, 0, 2, 3) && compare(0, 0, 1, 4, 0, 2, 0, 2) && compare(0, 0, 2, 4, 0, 1, 2, 3) && compare(0, 0, 2, 3, 0, 2, 0, 2) && compare(0, 0, 2, 4, 0, 2, 2, 2) && compare(0, 1, 0, 5, 0, 2, 0, 5) && compare(0, 1, 2, 3, 0, 2, 2, 2) && compare(0, 2, 1, 2, 0, 2, 2, 3))
			{
				split("R' U' F' R U R' U' R' F R2 U' R' U' R U R' U R"); // F
				break;
			}
			
			else if (compare(0, 0, 0, 4, 0, 1, 0, 5) && compare(0, 0, 0, 5, 0, 1, 2, 3) && compare(0, 0, 0, 5, 0, 2, 0, 5) && compare(0, 0, 0, 4, 0, 2, 2, 3) && compare(0, 0, 1, 4, 0, 0, 2, 3) && compare(0, 0, 1, 4, 0, 2, 0, 2) && compare(0, 0, 2, 3, 0, 2, 0, 2) && compare(0, 0, 2, 4, 0, 2, 1, 2) && compare(0, 0, 2, 4, 0, 2, 2, 2) && compare(0, 1, 0, 5, 0, 2, 2, 3) && compare(0, 1, 2, 3, 0, 2, 0, 5) && compare(0, 2, 1, 2, 0, 2, 2, 2))
			{
				split("R2 U R' U R' U' R U' R2 D U' R' U R D'"); // Ga
				break;
			}
			
			else if (compare(0, 0, 0, 5, 0, 0, 1, 4) && compare(0, 0, 0, 5, 0, 2, 0, 5) && compare(0, 0, 0, 4, 0, 2, 1, 2) && compare(0, 0, 0, 4, 0, 2, 2, 3) && compare(0, 0, 1, 4, 0, 2, 0, 5) && compare(0, 0, 2, 4, 0, 1, 0, 5) && compare(0, 0, 2, 3, 0, 1, 2, 3) && compare(0, 0, 2, 3, 0, 2, 0, 2) && compare(0, 0, 2, 4, 0, 2, 2, 2) && compare(0, 1, 0, 5, 0, 2, 2, 2) && compare(0, 1, 2, 3, 0, 2, 0, 2) && compare(0, 2, 1, 2, 0, 2, 2, 3))
			{
				split("R' U' R U D' R2 U R' U R U' R U' R2 D"); // Gb
				break;
			}
			
			else if (compare(0, 0, 0, 5, 0, 1, 2, 3) && compare(0, 0, 0, 5, 0, 2, 0, 5) && compare(0, 0, 0, 4, 0, 2, 1, 2) && compare(0, 0, 0, 4, 0, 2, 2, 3) && compare(0, 0, 1, 4, 0, 0, 2, 4) && compare(0, 0, 1, 4, 0, 2, 2, 2) && compare(0, 0, 2, 3, 0, 1, 0, 5) && compare(0, 0, 2, 3, 0, 2, 0, 2) && compare(0, 0, 2, 4, 0, 2, 2, 2) && compare(0, 1, 0, 5, 0, 2, 0, 2) && compare(0, 1, 2, 3, 0, 2, 0, 5) && compare(0, 2, 1, 2, 0, 2, 2, 3))
			{
				split("R2 U' R U' R U R' U R2 D' U R U' R' D"); // Gc
				break;
			}
			
			else if (compare(0, 0, 0, 4, 0, 1, 2, 3) && compare(0, 0, 0, 5, 0, 2, 0, 5) && compare(0, 0, 0, 5, 0, 2, 1, 2) && compare(0, 0, 0, 4, 0, 2, 2, 3) && compare(0, 0, 1, 4, 0, 0, 2, 3) && compare(0, 0, 1, 4, 0, 2, 0, 2) && compare(0, 0, 2, 4, 0, 1, 0, 5) && compare(0, 0, 2, 3, 0, 2, 0, 2) && compare(0, 0, 2, 4, 0, 2, 2, 2) && compare(0, 1, 0, 5, 0, 2, 2, 2) && compare(0, 1, 2, 3, 0, 2, 2, 3) && compare(0, 2, 0, 5, 0, 2, 1, 2))
			{
				split("R U R' U' D R2 U' R U' R' U R' U R2 D'"); // Gd
				break;
			}
			
			else if (compare(0, 0, 0, 5, 0, 0, 1, 4) && compare(0, 0, 0, 5, 0, 0, 2, 3) && compare(0, 0, 0, 4, 0, 2, 0, 2) && compare(0, 0, 0, 4, 0, 2, 1, 2) && compare(0, 0, 1, 4, 0, 0, 2, 3) && compare(0, 0, 2, 4, 0, 1, 2, 3) && compare(0, 0, 2, 4, 0, 2, 2, 2) && compare(0, 1, 0, 5, 0, 2, 0, 5) && compare(0, 1, 0, 5, 0, 2, 2, 3) && compare(0, 1, 2, 3, 0, 2, 2, 2) && compare(0, 2, 0, 2, 0, 2, 1, 2) && compare(0, 2, 0, 5, 0, 2, 2, 3))
			{
				split("R' U R' U' B' R' B2 U' B' U B' R B R"); // V
				break;
			}
			
			else if (compare(0, 0, 0, 4, 0, 0, 1, 4) && compare(0, 0, 0, 5, 0, 0, 2, 3) && compare(0, 0, 0, 5, 0, 1, 2, 3) && compare(0, 0, 0, 4, 0, 2, 0, 2) && compare(0, 0, 1, 4, 0, 2, 0, 2) && compare(0, 0, 2, 3, 0, 1, 2, 3) && compare(0, 0, 2, 4, 0, 2, 1, 2) && compare(0, 0, 2, 4, 0, 2, 2, 2) && compare(0, 1, 0, 5, 0, 2, 0, 5) && compare(0, 1, 0, 5, 0, 2, 2, 3) && compare(0, 2, 0, 5, 0, 2, 2, 3) && compare(0, 2, 1, 2, 0, 2, 2, 2))
			{
				split("U L U' R U2' L' U L R' U' R U2' L' U R'"); // Na
				break;
			}
			
			else if (compare(0, 0, 0, 5, 0, 0, 2, 3) && compare(0, 0, 0, 5, 0, 1, 0, 5) && compare(0, 0, 0, 4, 0, 2, 0, 2) && compare(0, 0, 0, 4, 0, 2, 1, 2) && compare(0, 0, 1, 4, 0, 0, 2, 4) && compare(0, 0, 1, 4, 0, 2, 2, 2) && compare(0, 0, 2, 3, 0, 1, 0, 5) && compare(0, 0, 2, 4, 0, 2, 2, 2) && compare(0, 1, 2, 3, 0, 2, 0, 5) && compare(0, 1, 2, 3, 0, 2, 2, 3) && compare(0, 2, 0, 2, 0, 2, 1, 2) && compare(0, 2, 0, 5, 0, 2, 2, 3))
			{
				split("R' U R' F R F' R U' R' F' U F R U R' U' R"); // Nb
				break;
			}
			
			else if (compare(0, 0, 0, 5, 0, 0, 2, 3) && compare(0, 0, 0, 5, 0, 1, 2, 3) && compare(0, 0, 0, 4, 0, 2, 0, 2) && compare(0, 0, 0, 4, 0, 2, 1, 2) && compare(0, 0, 1, 4, 0, 2, 0, 5) && compare(0, 0, 1, 4, 0, 2, 2, 3) && compare(0, 0, 2, 4, 0, 1, 0, 5) && compare(0, 0, 2, 3, 0, 1, 2, 3) && compare(0, 0, 2, 4, 0, 2, 2, 2) && compare(0, 1, 0, 5, 0, 2, 2, 2) && compare(0, 2, 0, 2, 0, 2, 1, 2) && compare(0, 2, 0, 5, 0, 2, 2, 3))
			{
				split("F R U' R' U' R U R' F' R U R' U' R' F R F'"); // Y
				break;
			}
			
			split("U");
			print_cube();
		}
	}
	if (compare(0, 1, 0, 5, 1, 2, 1, 2))
		split("U'");
	else if (compare(0, 1, 2, 3, 1, 2, 1, 2))
		split("U");
	else if (compare(0, 0, 1, 4, 1, 2, 1, 2))
		split("U2");
	print_cube();
}


void clear_near_cube()
{
	int i, j;
	attron(COLOR_PAIR(0));
	for (i = 0; i < 27; i++)
		for (j = 0; j < 65; j++)
			mvprintw(i, j, " ");
	attroff(COLOR_PAIR(0));
}
