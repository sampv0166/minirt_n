#include "../../include/minirt.h"

static void		init_objects(t_rt *rt)
{
	rt->sphere = NULL;
	rt->plane = NULL;
	rt->cylinder = NULL;
}

static void		init_light(t_rt *rt)
{
	t_light	*baselight;

	baselight = (t_light *)ec_malloc(sizeof(t_light));
	baselight->pos.x = 0;
	baselight->pos.y = 0;
	baselight->pos.z = 0;
	baselight->pos.w = 1;
	baselight->light = 0;
	baselight->color.r = 0;
	baselight->color.g = 0;
	baselight->color.b = 0;
	baselight->intensity = create_rgba(0, 0, 0, 0);
	rt->light = baselight;
}

static void		init_camera(t_rt *rt)
{
	t_cam	*basecam;

	basecam = (t_cam *)ec_malloc(sizeof(t_cam));
	basecam->view.x = 0;
	basecam->view.y = 0;
	basecam->view.z = 0;
	basecam->view.w = 1;
	basecam->pos.x = 0;
	basecam->pos.y = 0;
	basecam->pos.z = 1;
	basecam->pos.w = 0;
	basecam->fov = 0;
	basecam->origin = create_tuple(0, 0, 0, 1);
	rt->cam = basecam;
}

static void		init_qts(t_rt *rt)
{
	rt->qts = (t_qts) {0};
}


void			init_rt(t_rt *rt)
{
	t_ambi	ambi;

	init_qts(rt);
	ambi.light = 0.0;
	ambi.color.b = 0;
	ambi.color.r = 0;
	ambi.color.g = 0;
	rt->ambi = ambi;
	init_camera(rt);
	init_light(rt);
	init_objects(rt);
}
