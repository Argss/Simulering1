#pragma once

const static float MINVREL = 0.5; // minsta hastigheten som betraktas som kollision (vilande |v| < MINVREL)

const static int REPEATCOLLISIONDETECTION = 3; //maximalt antal iterationer vid kollisionsdetektering

const static int REPEATCONSTRAINTS = 3; //Hur många gånger constraints skall appliceras (upprepas)

const static float BIGFLOAT = 99999999; // Plattformsoberoende stort tal

const static float SMALLTHRESHOLD = 0.0001; //För att undvika jämförelse med noll

/*
 (c)2015 Henrik Engström, henrik.engstrom@his.se
 This code may only be used by students in the Game Physics course at the University of Skövde
 Contact me if you want to use it for other purposes.
 */