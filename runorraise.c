void
runorraise(const Arg *arg) {
    const char **app = arg->v;
    Arg a = { .ui = ~0 };
    Monitor *mon;
    Client *c;
    XClassHint hint = { NULL, NULL };

/* Tries to find the client */
  for (mon = mons; mon; mon = mon->next) {
    for (c = mon->clients; c; c = c->next) {
      XGetClassHint(dpy, c->win, &hint);
      if (hint.res_class && strcmp(app[2], hint.res_class) == 0) {
        a.ui = c->tags;
        view(&a);
        focus(c);
        return;
      }
    }
  }
  /* Client not found: spawn it */
  spawn(arg);
} 
