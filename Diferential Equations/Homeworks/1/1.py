import numpy as np
import itertools
import plotly.figure_factory as ff
import plotly.graph_objects as go

x,y = np.meshgrid(np.arange(-3, 3, .1), np.arange(-3, 3, .1))
m = np.power(y,2)-x
#m = -np.multiply(x,y)
u = 1
v = np.multiply(m,u)
u,v = u/np.sqrt(np.power(u,2)+np.power(v,2)), v/np.sqrt(np.power(u,2)+np.power(v,2))

fig = ff.create_quiver(
	x = x,
	y = y,
	u = u,
	v = v,
	# scale=.2,
    arrow_scale=.001,
    line_width=1
)

fig.add_traces(
    [go.Scatter(
        x = x[0],
        y = x0*np.exp(-np.power(x[0],2)/2),
    ) for x0 in np.linspace(-2.5,2.5,50)]
)

fig.update_layout(
	template="simple_white",
    title="Hola",
    showlegend=False,
    width=1000,
    height=1000
)

fig.update_xaxes(showline=False, zeroline=False)
fig.update_yaxes(showline=False, zeroline=False)

fig.show()