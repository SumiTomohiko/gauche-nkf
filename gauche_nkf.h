/*
 * gauche_nkf.h
 */

/* Prologue */
#ifndef GAUCHE_GAUCHE_NKF_H
#define GAUCHE_GAUCHE_NKF_H

#include <gauche.h>
#include <gauche/extend.h>

SCM_DECL_BEGIN

extern ScmObj Scm_Nkf(ScmObj opts, const char* s);

/* Epilogue */
SCM_DECL_END

#endif  /* GAUCHE_GAUCHE_NKF_H */
