/* 
 * Q(uirky) Stack
 *
 * +---------------------------+
 * |                           |
 * |                           |
 * |                           |
 * |                           |
 * |                           |
 * +-------------+-------------+
 * |             |             |
 * +-------------+-------------+
 * |             |             |
 * +-------------+-------------+
 * |                           |
 * +---------------------------+
 *
 */
static void qstack(void)
{
	unsigned int i, n, nx, ny, nw, nh, m, mh, th, dy;
	Client *c;
  bool next = false;

	for (n = 0, c = nextvisible(clients); c; c = nextvisible(c->next))
		if (!c->minimized)
			n++;

	m  = MAX(1, MIN(n, screen.nmaster));
	mh = (n == m ? wah : screen.mfact * wah);
	th = n == m ? 0 : 2 * (wah - mh) / (n - m);
	ny = way;

	for (i = 0, c = nextvisible(clients); c; c = nextvisible(c->next)) {
		if (c->minimized)
			continue;
		if (i < m) { /* master */
      nx = wax;
      nw = waw;
			nh = (i < m - 1) ? mh / m : (way + mh) - ny;
      dy = nh;
		} else {/* tile window */
      if(i%2!=0){
        if(i==n-1){
          nx = wax;
          nw = waw;
          nh = (i < n - 1) ? th : (way + wah) - ny;
          next = !next;
          dy = 0;
        } else {
          nx = wax;
          nw = waw / 2;
          nh = (i < n - 1) ? th : (way + wah) - ny;
          next = !next;
          dy = 0;
        }
      } else if( next) {
        nw = waw / 2;
        nx = wax + nw;
        nh = (i < n - 1) ? th : (way + wah) - ny;
        next = !next;
        dy = nh;
				mvvline(ny, nx, ACS_VLINE, nh);
				mvaddch(ny, nx, ACS_TTEE);
        nx++;
        nw--;
      } else {
        nx = wax;
        nw = waw;
        nh = (i < n - 1) ? th : (way + wah) - ny;
        dy = nh;
      }
    }
		resize(c, nx, ny, nw, nh);
    ny += dy;
		i++;
	}
}
