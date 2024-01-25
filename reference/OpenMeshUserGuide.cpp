#include <OpenMeshWarpper.h>




//openmesh使用半边结构表示网格的拓扑关系，主要操作对象为顶点、半边、边、面
//参考图中示意，具体参考openmesh官方地址


/*                             A
                               /\
							  /  \
							 /    \
							/      \
						 B /------->\ C
						   \<-------/ 
						    \      /
							 \    /
							  \  /
							   \/
							   D
*/

void func()
{
	Triangle_mesh mesh;
	//遍历顶点
	auto v_end = mesh.vertices_end();
	for (auto v_it = mesh.vertices_begin(); v_it != v_end; ++v_it)//迭代器
	{
		//vh为顶点坐标对应handle，简单理解为地址
		VertexHandle vh = *v_it;
		//p为顶点坐标
		Point p = mesh.point(vh);
		//也可以根据顶点访问其1邻域顶点,可以指定顺时针或者逆时针访问
		auto vv_it = mesh.vv_iter(vh); 
		auto vv_ccwit = mesh.vv_ccwiter(vh); //逆时针访问
		for (; vv_it.is_valid(); ++vv_it)
		{
			VertexHandle ringvh = *vv_it;
		}
		//访问顶点的邻域边,指定逆时针访问
		auto ve_it = mesh.ve_ccwiter(vh);
		for (; ve_it.is_valid(); ++ve_it)
		{
			EdgeHandle eh = *ve_it;
			//根据边访问获得两个半边
			HalfedgeHandle hh0 = mesh.halfedge_handle(eh, 0);
			HalfedgeHandle hh1 = mesh.halfedge_handle(eh, 1);
			//根据半边获得顶点,假设hh0为BC半边，则vh0对应B，vh1对应C
			VertexHandle vh0 = mesh.from_vertex_handle(hh0);
			VertexHandle vh1 = mesh.to_vertex_handle(hh0);
			//根据半边获得面信息,一个半边对应唯一一个面，如果没有面则为边界
			FaceHandle fh = mesh.face_handle(hh0);
		}
	}
	//同理访问面
	auto f_end = mesh.faces_end();
	for (auto f_it = mesh.faces_begin(); f_it != f_end; ++f_it)
	{
		//fh为面handle
		FaceHandle fh = *f_it;
		//根据fh逆时针访问三个顶点
		VertexHandle vhs[3];
		int index = 0;
		auto fv_ccw_it = mesh.fv_ccwiter(fh);
		for (; fv_ccw_it.is_valid(); ++fv_ccw_it)
		{
			//逆时针获得三角面的每个顶点
			vhs[index] = *fv_ccw_it;
			index++;
		}
		vhs[0] = *fv_ccw_it;
		vhs[1] = *(++fv_ccw_it);
		vhs[2] = *(++fv_ccw_it);
		//也可以根据面访问该面的边和半边
		auto fe_it = mesh.fe_ccwiter(fh);
		auto fh_it = mesh.fh_ccwiter(fh);
		for (; fh_it.is_valid(); ++fh_it)
		{
			HalfedgeHandle hh = *fh_it;
		}
	}
	//访问边同理
	//判断是否是边界,参数可以是面、顶点、半边、边
	//还有其他是否为流形等的判断
	VertexHandle vh;
	mesh.is_boundary(vh);


	//openmesh提供了为边、顶点、面添加额外信息的功能
	//比如下面为每个顶点添加一个权重
	OpenMesh::VPropHandleT<float>  vweights;
	mesh.add_property(vweights, "vweights");
	for (auto v_it = mesh.vertices_begin(); v_it != v_end; ++v_it)
	{
		mesh.property(vweights, vh) = 1.0f;
		float w = mesh.property(vweights, vh);
	}
	//使用完成后删除这个属性，释放内存
	mesh.remove_property(vweights);


    //删除元素都提供了相应接口,注意删除前需要分配标记位,和前面添加额外信息意思一样
	//只是这里给我们提供了一些默认的
	mesh.request_vertex_status();
	mesh.request_edge_status();
	mesh.request_face_status();
	mesh.delete_vertex(vh);
	//删除后一定要调用下面函数，这些元素才会在内存中被删除，不然仅仅标记为删除状态
	//前面的状态请求就是为了标记删除状态
	mesh.garbage_collection();



	//下面提供一个实例,读入一颗牙齿，我们顺序找到这些牙齿的边界顶点
	//假设牙齿只有一条封闭边界
	//读入网格数据
	OpenMesh::IO::read_mesh(mesh,"D:\\TOOTH.stl");
	HalfedgeHandle hh;
	for (auto h_it = mesh.halfedges_begin(); h_it != mesh.halfedges_end(); ++h_it)
	{
		if (mesh.is_boundary(*h_it))
		{
			hh = *h_it;
			break;
		}
	}
	//如果模型是封闭的则没有边界
	if (!hh.is_valid())
		return;
	std::vector<VertexHandle>  boundaryvh;
	HalfedgeHandle currenthh = hh;
	do
	{
		boundaryvh.push_back( mesh.to_vertex_handle(currenthh) );
		currenthh = mesh.next_halfedge_handle(currenthh);
	} while (currenthh!=hh);
}


