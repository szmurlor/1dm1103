#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * Program demontruje utworzenie procesu potomnego, który uruchamia nowy proces pomocą
 * `execlp`. Nowy proces podmienia stary proces. W nowym procesie jego standardowe
 * wyjście jest przekierowane do strumienia (ang. pipe), który jest
 * przechwytywany przez proces (oryginalny) rodzica.
 */
int main(int argc, char ** argv) {
	int child;
	int p[2];
	// p[0] - będzie używane do odczytu
	// p[1] - będzie używane do zapisu

	//* Tworzę strumień, umożliwiający jednokierunkową komunikację miedzy procesami
	pipe(p);
	if ((child = fork()) == 0) {
		//* to jest kod wykonywny przez proces potomny, poniewaz for zwrócił wartość 0.
		printf("Identyfikator pid mojego rodzica to: %d\n", getppid());

		//* Kopiuję uchwyt strumień wyjściowy p[1] w miejsce uchwytu identyfikującego 
		//* standardowe wyjście (stdout = 1, do strumienia umożliwiającego komunikację międzyprocesową)
		dup2(p[1], 1);
		close(p[0]);

		//* Uruchamiam nowy proces - program `ls`, który ma wyświetlić zawartość bieżącego katalogu,
		//* pamiętajmy, że jego standardowe wyjście będzie zduplikowane do strumienia.
		//execlp("ls", "ls", (const char*) NULL);
		printf("To się nie wyświetli nigdzie, bo podmieniony został proces :-(.\n");
	} else {
		//* Miejsce na zapisywanie danych wypisanych przez proces potomny
		
		char buf[1024];
		int n;

		printf("Identyfikator mojego dziecka to: %d\n", child);

		close(p[1]);
		while( (n = read(p[0], buf, 1024)) > 0) {
			buf[n] = 0; //* potrzebne, bo dalej użyjemy printfa, który
			printf("Otrzymałem od dziecka: %s\n", buf);
		}
		printf("Zakończyłem proces rodzica.\n");
	}
}
