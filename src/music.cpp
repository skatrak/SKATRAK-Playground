/**
 * @brief Inicializa la clase con los valores por defecto e inicia SDL
 */
music_t::music_t(): music(NULL), music_names(NULL), n_tracks(0), volume(128), current(0), playing(false), paused(false) {
	if(!Mix_Init(MIX_INIT_OGG) || !Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096)){
		running = false;
		fprintf(stderr, "No se ha podido inicializar el sistema de audio.\n");
	}
	else {
		running = true;
		Mix_HookMusicFinished(nextTrack);
	}
}

/**
 * @brief Inicializa la clase con los valores por defecto, inicia SDL y reserva espacio para un número de canciones
 * @param nT Número de canciones que deseas poder reproducir cíclicamente
 */
music_t::music_t(int nT): music(NULL), music_names(NULL), volume(128), current(0), playing(false), paused(false), n_tracks(nT) {
	if(!Mix_Init(MIX_INIT_OGG) || !Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096)){
		running = false;
		fprintf(stderr, "No se ha podido inicializar el sistema de audio.\n");
	}
	else {
		running = true;
		setTracks(n_tracks);
		Mix_HookMusicFinished(nextTrack);
	}
}

/**
 * @brief Destructor. Libera la memoria ocupada por todas las canciones.
 */
music_t::~music_t(){
	if(music != NULL){
		for(int i = 0; i < n_tracks; i++)
			Mix_FreeMusic(music[i]);
		delete [] music;
		music = NULL;
		Mix_HookMusicFinished(NULL);
	}
	if(music_names != NULL)
		delete [] music_names;
	n_tracks = 0;
	volume = 0;
	running = false;
}

void music_t::setTracks(int n){
	if(playing)
		halt();
	n_tracks = n;
	if(music != NULL){
		for(int i = 0; i < n_tracks; i++)
			Mix_FreeMusic(music[i]);
		delete [] music;
	}
	if(music_names != NULL)
		delete [] music_names;
	music = new Mix_Music*[n_tracks];
	if(music == NULL)
		fprintf(stderr, "Error en la reserva de memoria para la lista de reproducción.\n");
	else {
		for(int i = 0; i < n_tracks; i++)
			music[i] = NULL;
	}
	music_names = new string[n_tracks];
	if(music_names == NULL)
		fprintf(stderr, "Error en la reserva de memoria para los nombres de las canciones de la lista de reproducción.\n");
}

void music_t::setTrack(int index, string name){
	if(index < 0 || index >= n_tracks){
		fprintf(stderr, "Se ha intentado cargar una canción en una zona de memoria no reservada. Se sobreescribirá la primera canción.\n");
		index = 0;
	}
	if(music != NULL && music_names != NULL){
		music_names[index] = name;
		if(music[index] != NULL){
			Mix_FreeMusic(music[index]);
			music[index] = NULL;
		}
		music[index] = Mix_LoadMUS(name.c_str());
		if(!music[index]){
			fprintf(stderr, "No se ha podido cargar el fichero \"%s\".\n", name.c_str());
			music[index] = NULL;
		}
	}
	else
		fprintf(stderr, "No se puede cargar ninguna canción en memoria porque no se ha reservado previamente.\n");
}

void music_t::play(){
	if(running){
		if(!playing){
			if(!paused){
				Mix_PlayMusic(music[current], 0);
				playing = true;
			}
			else {
				Mix_ResumeMusic();
				paused = false;
			}
		}
	}
	else
		fprintf(stderr, "No se puede reproducir la música porque no se ha inicializado correctamente.\n");
}

void music_t::pause(){
	if(running && playing && !paused){
		Mix_PauseMusic();
		paused = true;
	}
}

void music_t::halt(){
	if(running && playing){
		Mix_HaltMusic();
		playing = false;
		paused = false;
	}
}

void music_t::setVol(int vol){
	if(vol != volume && vol >= 0 && vol <= 128)
		Mix_VolumeMusic(vol);
}
