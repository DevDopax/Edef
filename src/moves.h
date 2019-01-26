void U()
{
	mvprintw(11, 59, "/___");
	mvprintw(12, 59, "\\");
}

void U2()
{
	mvprintw(11, 59, "/_2x");
	mvprintw(12, 59, "\\");
}

void U_inverse()
{
	mvprintw(11, 1, "___\\");
	mvprintw(12, 4, "/");
}

void U2_inverse()
{
	mvprintw(11, 1, "2x_\\");
	mvprintw(12, 4, "/");
}

void E()
{
	mvprintw(13, 1, "___\\");
	mvprintw(14, 4, "/");
}

void E2()
{
	mvprintw(13, 1, "2x_\\");
	mvprintw(14, 4, "/");
}

void E_inverse()
{
	mvprintw(13, 59, "/___");
	mvprintw(14, 59, "\\");
}

void E2_inverse()
{
	mvprintw(13, 59, "/_2x");
	mvprintw(14, 59, "\\");
}

void D()
{
	mvprintw(15, 1, "___\\");
	mvprintw(16, 4, "/");
}

void D2()
{
	mvprintw(15, 1, "2x_\\");
	mvprintw(16, 4, "/");
}

void D_inverse()
{
	mvprintw(15, 59, "/___");
	mvprintw(16, 59, "\\");
}

void D2_inverse()
{
	mvprintw(15, 59, "/_2x");
	mvprintw(16, 59, "\\");
}

void Uw()
{
	U();
	E_inverse();
}

void Uw2()
{
	U2();
	E2_inverse();
}

void Uw_inverse()
{
	U_inverse();
	E();
}

void Uw2_inverse()
{
	U2_inverse();
	E2();
}

void Dw()
{
	E();
	D();
}

void Dw2()
{
	E2();
	D2();
}

void Dw_inverse()
{
	E_inverse();
	D_inverse();
}

void Dw2_inverse()
{
	E2_inverse();
	D2_inverse();
}

void L()
{
	mvprintw(1, 20, "|");
	mvprintw(2, 19, "\\|/");
	mvprintw(3, 20, "¯");
}

void L2()
{
	mvprintw(1, 19, "2x");
	mvprintw(2, 19, "\\|/");
	mvprintw(3, 20, "¯");
}

void L_inverse()
{
	mvprintw(24, 20, "_");
	mvprintw(25, 19, "/|\\");
	mvprintw(26, 20, "|");
}

void L2_inverse()
{
	mvprintw(24, 20, "_");
	mvprintw(25, 19, "/|\\");
	mvprintw(26, 19, "2x");
}

void M()
{
	mvprintw(1, 24, "|");
	mvprintw(2, 23, "\\|/");
	mvprintw(3, 24, "¯");
}

void M2()
{
	mvprintw(1, 23, "2x");
	mvprintw(2, 23, "\\|/");
	mvprintw(3, 24, "¯");
}

void M_inverse()
{
	mvprintw(24, 24, "_");
	mvprintw(25, 23, "/|\\");
	mvprintw(26, 24, "|");
}

void M2_inverse()
{
	mvprintw(24, 24, "_");
	mvprintw(25, 23, "/|\\");
	mvprintw(26, 23, "2x");
}

void R()
{
	mvprintw(24, 28, "_");
	mvprintw(25, 27, "/|\\");
	mvprintw(26, 28, "|");
}

void R2()
{
	mvprintw(24, 28, "_");
	mvprintw(25, 27, "/|\\");
	mvprintw(26, 27, "2x");
}

void R_inverse()
{
	mvprintw(1, 28, "|");
	mvprintw(2, 27, "\\|/");
	mvprintw(3, 28, "¯");
}

void R2_inverse()
{
	mvprintw(1, 27, "2x");
	mvprintw(2, 27, "\\|/");
	mvprintw(3, 28, "¯");
}

void Lw()
{
	L();
	M();
}

void Lw2()
{
	L2();
	M2();
}

void Lw_inverse()
{
	L_inverse();
	M_inverse();
}

void Lw2_inverse()
{
	L2_inverse();
	M2_inverse();
}

void Rw()
{
	M_inverse();
	R();
}

void Rw2()
{
	M2_inverse();
	R2();
}

void Rw_inverse()
{
	M();
	R_inverse();
}

void Rw2_inverse()
{
	M2();
	R2_inverse();
}

void F()
{
	mvprintw(8, 14, " ___\\");
	mvprintw(9, 14, "|   /");
	mvprintw(10, 14, "|");
}

void F2()
{
	mvprintw(8, 14, " 2x_\\");
	mvprintw(9, 14, "|   /");
	mvprintw(10, 14, "|");
}

void F_inverse()
{
	mvprintw(8, 31, "/___");
	mvprintw(9, 31, "\\   |");
	mvprintw(10, 35, "|");
}

void F2_inverse()
{
	mvprintw(8, 31, "/_2x");
	mvprintw(9, 31, "\\   |");
	mvprintw(10, 35, "|");
}

void S()
{
	mvprintw(6, 10, " _______\\");
	mvprintw(7, 10, "|       /");
	mvprintw(8, 10, "|");
	mvprintw(9, 10, "|");
	mvprintw(10, 10, "|");
}

void S2()
{
	mvprintw(6, 10, " 2x_____\\");
	mvprintw(7, 10, "|       /");
	mvprintw(8, 10, "|");
	mvprintw(9, 10, "|");
	mvprintw(10, 10, "|");
}

void S_inverse()
{
	mvprintw(6, 31, "/_______");
	mvprintw(7, 31, "\\       |");
	mvprintw(8, 39, "|");
	mvprintw(9, 39, "|");
	mvprintw(10, 39, "|");
}

void S2_inverse()
{
	mvprintw(6, 31, "/_____2x");
	mvprintw(7, 31, "\\       |");
	mvprintw(8, 39, "|");
	mvprintw(9, 39, "|");
	mvprintw(10, 39, "|");
}

void B()
{
	mvprintw(4, 31, "/___________");
	mvprintw(5, 31, "\\           |");
	mvprintw(6, 43, "|");
	mvprintw(7, 43, "|");
	mvprintw(8, 43, "|");
	mvprintw(9, 43, "|");
	mvprintw(10, 43, "|");
}

void B2()
{
	mvprintw(4, 31, "/_________2x");
	mvprintw(5, 31, "\\           |");
	mvprintw(6, 43, "|");
	mvprintw(7, 43, "|");
	mvprintw(8, 43, "|");
	mvprintw(9, 43, "|");
	mvprintw(10, 43, "|");
}

void B_inverse()
{
	mvprintw(4, 6, " ___________\\");
	mvprintw(5, 6, "|           /");
	mvprintw(6, 6, "|");
	mvprintw(7, 6, "|");
	mvprintw(8, 6, "|");
	mvprintw(9, 6, "|");
	mvprintw(10, 6, "|");
}

void B2_inverse()
{
	mvprintw(4, 6, " 2x_________\\");
	mvprintw(5, 6, "|           /");
	mvprintw(6, 6, "|");
	mvprintw(7, 6, "|");
	mvprintw(8, 6, "|");
	mvprintw(9, 6, "|");
	mvprintw(10, 6, "|");
}

void Fw()
{
	F();
	S();
}

void Fw2()
{
	F2();
	S2();
}

void Fw_inverse()
{
	F_inverse();
	S_inverse();
}

void Fw2_inverse()
{
	F2_inverse();
	S2_inverse();
}

void Bw()
{
	S_inverse();
	B();
}

void Bw2()
{
	S2_inverse();
	B2();
}

void Bw_inverse()
{
	S();
	B_inverse();
}

void Bw2_inverse()
{
	S2();
	B2_inverse();
}

void X()
{
	L();
	M();
	R_inverse();
}

void X2()
{
	L2();
	M2();
	R2_inverse();
}

void X_inverse()
{
	L_inverse();
	M_inverse();
	R();
}

void X2_inverse()
{
	L2_inverse();
	M2_inverse();
	R2();
}

void Y()
{
	U();
	E_inverse();
	D_inverse();
}

void Y2()
{
	U2();
	E2_inverse();
	D2_inverse();
}

void Y_inverse()
{
	U_inverse();
	E();
	D();
}

void Y2_inverse()
{
	U2_inverse();
	E2();
	D2();
}

void Z()
{
	F();
	S();
	B_inverse();
}

void Z2()
{
	F2();
	S2();
	B2_inverse();
}

void Z_inverse()
{
	F_inverse();
	S_inverse();
	B();
}

void Z2_inverse()
{
	F2_inverse();
	S2_inverse();
	B2();
}
