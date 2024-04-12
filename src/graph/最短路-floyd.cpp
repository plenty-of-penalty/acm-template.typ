for (int i = 1; i <= n; i++) dis[i][i] = 0;
for (int k = 1; k <= n; k++)
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
      dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
    }