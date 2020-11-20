//glViewport(0, 0, 800, 600);
	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);	// Handeling resize

	/*float positions[] = {
		// front
		-1.0, -1.0,  1.0, 0.0f, 0.0f,
		 1.0, -1.0,  1.0, 0.0f, 1.0f,
		 1.0,  1.0,  1.0, 1.0f, 0.0f,
		-1.0,  1.0,  1.0, 1.0f, 1.0f,
		// back
		-1.0, -1.0, -1.0, 0.0f, 0.0f,
		 1.0, -1.0, -1.0, 0.0f, 1.0f,
		 1.0,  1.0, -1.0, 1.0f, 0.0f,
		-1.0,  1.0, -1.0, 1.0f, 1.0f,
	};


	unsigned int indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	VertexArray va;
	VertexBuffer vb(positions, 8 * 5 * sizeof(float));
	VertexBufferLayout layout;
	layout.push<float>(3);// 2D position values
	layout.push<float>(2);// 2D texture values
	va.addBuffer(vb, layout);

	IndexBuffer ib(indices, 36);*/



	/*for (int i = 0; i < v_texCoord.x = texCoord.x / 2;; i++) {
		if (i % 3 == 0)
			std :: cout << "\n";
		std::cout << v[i] << ",";
	}*/

	/*for (int i = 0; i < indCount; i++) {
		if (i % 3 == 0)
			std::cout << "\n";
		std::cout << idx[i] << ",";
	}*/

	/*float positions[] = {
		0.0f , 0.0f ,
		1.0f  , 0.0f ,
		0.0f  ,  1.0f ,
		1.0f ,  1.0f
	};*/

	/*float positions[] = {
		0.0f , 0.0f , 0.0f , 0.0f,
		1.0f  , 0.0f , 1.0f , 0.0f,
		0.0f  ,  1.0f , 1.0f , 1.0f,
		1.0f ,  1.0f , 0.0f , 1.0f
	};*/


	/*unsigned int indices[] = {
		0,2,1,
		2,3,0
	};*/


	/*void CreateGrid(float width, float depth, int m, int n, MeshData& meshData)
	{
		int vertexCount = m * n;
		int faceCount = (m - 1) * (n - 1) * 2;
		// Create the vertices.

		float halfWidth = 0.5f * width;
		float halfDepth = 0.5f * depth;

		float dx = width / (n - 1);
		float dz = depth / (m - 1);

		float du = 1.0f / (n - 1);
		float dv = 1.0f / (m - 1);


		meshData.Vertices.resize(vertexCount);
		for (float i = 0.0f; i < m; ++i)
		{
			float z = halfDepth - i * dz;
			for (float j = 0.0f; j < n; ++j)
			{
				//code
				float x = -halfWidth + j * dx;

				meshData.Vertices[i * n + j].x = x;
				meshData.Vertices[i * n + j].y = 0.0f;
				meshData.Vertices[i * n + j].z = z;

				meshData.Vertices[i * n + j].u = j * du;
				meshData.Vertices[i * n + j].v = i * dv;

				//vertex temp = {x, 0.0f, z, j*du, i*dv};
				//meshData.Vertices.push_back(temp);
			}
		}
		//indices
		meshData.Indices.resize(faceCount);

		unsigned int offset = 0;
		for (unsigned int i = 0; i < m - 1; ++i)
		{
			for (unsigned int j = 0; j < n - 1; ++j)
			{
				//offset = x * m;
				index temp =
				{
					i * n + j,
					i * n + j + 1,
					(i + 1) * n + j
				};

				index temp_2 =
				{
					(i + 1) * n + j,
					i * n + j + 1,
					(i + 1) * n + j + 1
				};

				meshData.Indices.push_back(temp);
				meshData.Indices.push_back(temp_2);
			}
		}
	}*/


	/*struct vertex
	{
		float x, y, z;
		float u, v;
	};

	struct index
	{
		unsigned int a, b, c;
	};

	struct MeshData
	{
		std::vector<vertex> Vertices;
		std::vector<index> Indices;
		//std::vector<unsigned int > Indices;
	};*/