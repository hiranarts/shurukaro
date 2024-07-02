#pragma once
int platformInit();
int platformDestroy(); 
/* a concat function for c style strings, this allocates memory */ 
char* concat(const char* s1, const char* s2);
/* This code loads a music file from the data path */
Mix_Music* platLoadMusic(const char* filepath);
