int reader(char *fichier)
{
	printf("begin reader\n");
	FILE *file = NULL;

	printf("Open file\n");
	file = fopen(fichier, "r");

	// il faut un sem_post
	if (file != NULL) { // file succesfully opened
		fractal_t *new_fract = NULL;
		char n[65] = {0};
		int w = 0;
		int h = 0;
		double a = 0.0;
		double b = 0.0;
		char line[500]; // maximal characters per line
		int ans_line = 0;

		while (fgets(line, sizeof(line),file)) {
			//BUG : sem is not declared
			// sem_wait(&sem); //sem_past doit etre appele a chaque creation d'un thread calculator
			if (sscanf(line, "%s %d %d %lf %lf", n, &w, &h, &a, &b) == 5
			&& line[0] != '#') {
				new_fract = fractal_new(n, w, h, a, b);
				int err = enqueue(new_fract); // BUG : buffer not declared
				if (err != 0) {
					fclose(file); // si il y a une erreur,s on arrete la lecture
					printf("Error : push didn't worked correctly\n");
					// error(err, "push \n"); // BUG : too few arguments to `error`
					exit(1);
				}
			}
		}
		fclose(file);
	} else {
		printf("Error: file pointer is null\n"); // del when code is finished
		exit(1);
	}

	return 0;
}