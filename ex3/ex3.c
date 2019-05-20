// Exercico 1.1
//Base.c
#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
/* ===================================================== */
/* Programa base (esqueleto) para aplica��es Windows */
/* ===================================================== */
// Cria uma janela de nome "Janela Principal" e pinta fundo de branco
// Modelo para programas Windows:
// Composto por 2 fun��es:
// WinMain() = Ponto de entrada dos programas windows
// 1) Define, cria e mostra a janela
// 2) Loop de recep��o de mensagens provenientes do Windows
// TrataEventos()= Processamentos da janela (pode ter outro nome)
// 1) � chamada pelo Windows (callback)
// 2) Executa c�digo em fun��o da mensagem recebida
LRESULT CALLBACK TrataEventos(HWND, UINT, WPARAM, LPARAM);
// Nome da classe da janela (para programas de uma s� janela, normalmente este nome �
// igual ao do pr�prio programa) "szprogName" � usado mais abaixo na defini��o das
// propriedades do objecto janela
TCHAR szProgName[] = TEXT("Base");
// ============================================================================
// FUN��O DE IN�CIO DO PROGRAMA: WinMain()
// ============================================================================
// Em Windows, o programa come�a sempre a sua execu��o na fun��o WinMain()que desempenha
// o papel da fun��o main() do C em modo consola WINAPI indica o "tipo da fun��o" (WINAPI
// para todas as declaradas nos headers do Windows e CALLBACK para as fun��es de
// processamento da janela)
// Par�metros:
// hInst: Gerado pelo Windows, � o handle (n�mero) da inst�ncia deste programa
// hPrevInst: Gerado pelo Windows, � sempre NULL para o NT (era usado no Windows 3.1)
// lpCmdLine: Gerado pelo Windows, � um ponteiro para uma string terminada por 0
// destinada a conter par�metros para o programa
// nCmdShow: Par�metro que especifica o modo de exibi��o da janela (usado em
// ShowWindow()
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd; // hWnd � o handler da janela, gerado mais abaixo por CreateWindow()
	MSG lpMsg; // MSG � uma estrutura definida no Windows para as mensagens
	WNDCLASSEX wcApp; // WNDCLASSEX � uma estrutura cujos membros servem para
	// definir as caracter�sticas da classe da janela
	// ============================================================================
	// 1. Defini��o das caracter�sticas da janela "wcApp"
	// (Valores dos elementos da estrutura "wcApp" do tipo WNDCLASSEX)
	// ============================================================================
	wcApp.cbSize = sizeof(WNDCLASSEX); // Tamanho da estrutura WNDCLASSEX
	wcApp.hInstance = hInst; // Inst�ncia da janela actualmente exibida
	// ("hInst" � par�metro de WinMain e vem
	// inicializada da�)
	wcApp.lpszClassName = szProgName; // Nome da janela (neste caso = nome do programa)
	wcApp.lpfnWndProc = TrataEventos; // Endere�o da fun��o de processamento da janela
	// ("TrataEventos" foi declarada no in�cio e
	// encontra-se mais abaixo)
	wcApp.style = CS_HREDRAW | CS_VREDRAW;// Estilo da janela: Fazer o redraw se for
	// modificada horizontal ou verticalmente
	wcApp.hIcon = LoadIcon(NULL, IDI_APPLICATION);// "hIcon" = handler do �con normal
	//"NULL" = Icon definido no Windows
	// "IDI_AP..." �cone "aplica��o"
	wcApp.hIconSm = LoadIcon(NULL, IDI_ERROR);// "hIconSm" = handler do �con pequeno
	//"NULL" = Icon definido no Windows
	// "IDI_INF..." �con de informa��o
	wcApp.hCursor = LoadCursor(NULL, IDC_ARROW); // "hCursor" = handler do cursor (rato)
	// "NULL" = Forma definida no Windows
	// "IDC_ARROW" Aspecto "seta"
	wcApp.lpszMenuName = NULL; // Classe do menu que a janela pode ter
	// (NULL = n�o tem menu)
	wcApp.cbClsExtra = 0; // Livre, para uso particular
	wcApp.cbWndExtra = 0; // Livre, para uso particular
	wcApp.hbrBackground = CreateSolidBrush(RGB(255, 0, 0)); //(HBRUSH)GetStockObject(WHITE_BRUSH);
	// "hbrBackground" = handler para "brush" de pintura do fundo da janela. Devolvido por
	// "GetStockObject".Neste caso o fundo ser� branco
	// ============================================================================
	// 2. Registar a classe "wcApp" no Windows
	// ============================================================================
	if (!RegisterClassEx(&wcApp))
		return(0);
	// ============================================================================
	// 3. Criar a janela
	// ============================================================================
	hWnd = CreateWindow(
		szProgName, // Nome da janela (programa) definido acima
		TEXT("SO2 Ficha6 ex1"),// Texto que figura na barra do t�tulo
		WS_OVERLAPPEDWINDOW, // Estilo da janela (WS_OVERLAPPED= normal)
		5, // Posi��o x pixels (default=� direita da �ltima)
		5, // Posi��o y pixels (default=abaixo da �ltima)
		800, // Largura da janela (em pixels)
		600, // Altura da janela (em pixels)
		(HWND)HWND_DESKTOP, // handle da janela pai (se se criar uma a partir de
		// outra) ou HWND_DESKTOP se a janela for a primeira,
// criada a partir do "desktop"
(HMENU)NULL, // handle do menu da janela (se tiver menu)
(HINSTANCE)hInst, // handle da inst�ncia do programa actual ("hInst" �
// passado num dos par�metros de WinMain()
0); // N�o h� par�metros adicionais para a janela
// ============================================================================
// 4. Mostrar a janela
// ============================================================================
	ShowWindow(hWnd, nCmdShow); // "hWnd"= handler da janela, devolvido por
	// "CreateWindow"; "nCmdShow"= modo de exibi��o (p.e.
	// normal/modal); � passado como par�metro de WinMain()
	UpdateWindow(hWnd); // Refrescar a janela (Windows envia � janela uma
	// mensagem para pintar, mostrar dados, (refrescar)�
	// ============================================================================
	// 5. Loop de Mensagens
	// ============================================================================
	// O Windows envia mensagens �s janelas (programas). Estas mensagens ficam numa fila de
	// espera at� que GetMessage(...) possa ler "a mensagem seguinte"
	// Par�metros de "getMessage":
	// 1)"&lpMsg"=Endere�o de uma estrutura do tipo MSG ("MSG lpMsg" ja foi declarada no
	// in�cio de WinMain()):
	// HWND hwnd handler da janela a que se destina a mensagem
	// UINT message Identificador da mensagem
	// WPARAM wParam Par�metro, p.e. c�digo da tecla premida
	// LPARAM lParam Par�metro, p.e. se ALT tamb�m estava premida
	// DWORD time Hora a que a mensagem foi enviada pelo Windows
	// POINT pt Localiza��o do mouse (x, y)
	// 2)handle da window para a qual se pretendem receber mensagens (=NULL se se pretendem
	// receber as mensagens para todas as janelas pertencentes � thread actual)
	// 3)C�digo limite inferior das mensagens que se pretendem receber
	// 4)C�digo limite superior das mensagens que se pretendem receber
	// NOTA: GetMessage() devolve 0 quando for recebida a mensagem de fecho da janela,
	// terminando ent�o o loop de recep��o de mensagens, e o programa
	while (GetMessage(&lpMsg, NULL, 0, 0)) {
		TranslateMessage(&lpMsg); // Pr�-processamento da mensagem (p.e. obter c�digo
		// ASCII da tecla premida)
		DispatchMessage(&lpMsg); // Enviar a mensagem traduzida de volta ao Windows, que
		// aguarda at� que a possa reenviar � fun��o de
		// tratamento da janela, CALLBACK TrataEventos (abaixo)
	}
	// ============================================================================
	// 6. Fim do programa
	// ============================================================================
	return((int)lpMsg.wParam); // Retorna sempre o par�metro wParam da estrutura lpMsg
}
// ============================================================================
// FUN��O DE PROCESSAMENTO DA JANELA
// Esta fun��o pode ter um nome qualquer: Apenas � neces�rio que na inicializa��o da
// estrutura "wcApp", feita no in�cio de WinMain(), se identifique essa fun��o. Neste
// caso "wcApp.lpfnWndProc = WndProc"
//
// WndProc recebe as mensagens enviadas pelo Windows (depois de lidas e pr�-processadas
// no loop "while" da fun��o WinMain()
//
// Par�metros:
// hWnd O handler da janela, obtido no CreateWindow()
// messg Ponteiro para a estrutura mensagem (ver estrutura em 5. Loop...
// wParam O par�metro wParam da estrutura messg (a mensagem)
// lParam O par�metro lParam desta mesma estrutura
//
// NOTA:Estes par�metros est�o aqui acess�veis o que simplifica o acesso aos seus valores
//
// A fun��o EndProc � sempre do tipo "switch..." com "cases" que descriminam a mensagem
// recebida e a tratar. Estas mensagens s�o identificadas por constantes (p.e.
// WM_DESTROY, WM_CHAR, WM_KEYDOWN, WM_PAINT...) definidas em windows.h
//============================================================================
int num_clicks = 0;
int xPos, yPos;
TCHAR c = '?';

LRESULT CALLBACK TrataEventos(HWND hWnd, UINT messg, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;
	TCHAR text_clicks[20];

	switch (messg) {
	case WM_RBUTTONDOWN:
		num_clicks++;
		_stprintf_s(text_clicks, 20, TEXT("Num. de Clicks = %d"), num_clicks);
		InvalidateRect(hWnd, &rect, FALSE);
		//hdc = GetDC(hWnd);
		//GetClientRect(hWnd, &rect);
		//SetTextColor(hdc, RGB(255, 255, 255));
		//SetBkMode(hdc, TRANSPARENT);
		rect.left = 5 + num_clicks * 15;
		rect.top = 5 + num_clicks * 15;
		//DrawText(hdc, text_clicks, -1, &rect, DT_SINGLELINE | DT_NOCLIP);
		//ReleaseDC(hWnd, hdc);
		break;

	case WM_LBUTTONDOWN:
		xPos = GET_X_LPARAM(lParam);
		yPos = GET_Y_LPARAM(lParam);
		InvalidateRect(hWnd, NULL, FALSE);
		//hdc = GetDC(hWnd);
		//GetClientRect(hWnd, &rect);
		//SetTextColor(hdc, RGB(255, 255, 255));
		//SetBkMode(hdc, TRANSPARENT);
		//rect.left = xPos;
		//rect.top = yPos;
		//DrawText(hdc, &c, 1, &rect, DT_SINGLELINE | DT_NOCLIP);
		//ReleaseDC(hWnd, hdc);
		break;

	case WM_CHAR:
		c = (TCHAR)wParam;
		InvalidateRect(hWnd, NULL, FALSE);

		//hdc = GetDC(hWnd);
		//GetClientRect(hWnd, &rect);
		//SetTextColor(hdc, RGB(255, 255, 255));
		//SetBkMode(hdc, TRANSPARENT);
		//rect.left = xPos;
		//rect.top = yPos;
		//DrawText(hdc, &c, 1, &rect, DT_SINGLELINE | DT_NOCLIP);
		//ReleaseDC(hWnd, hdc);
		break;

	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);

		GetClientRect(hWnd, &rect);
		SetTextColor(hdc, RGB(255, 255, 255));
		SetBkMode(hdc, TRANSPARENT);
		rect.left = xPos;
		rect.top = yPos;
		DrawText(hdc, &c, 1, &rect, DT_SINGLELINE | DT_NOCLIP);

		EndPaint(hWnd, &ps);

		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, TEXT("Are you sure?"), TEXT("Quit Application"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES) {
			DestroyWindow(hWnd);
		}
		break;

	case WM_DESTROY: // Destruir a janela e terminar o programa
		// "PostQuitMessage(Exit Status)"
		PostQuitMessage(0);
		break;
	default:
		// Neste exemplo, para qualquer outra mensagem (p.e. "minimizar","maximizar","restaurar")
		// n�o � efectuado nenhum processamento, apenas se segue o "default" do Windows
		return DefWindowProc(hWnd, messg, wParam, lParam);
		break;
	}
	return(0);
}