#include "zen/core/base/scene_graph.h"

namespace zen {

SceneGraph::SceneGraph() {}

void SceneGraph::CreateEntity() {
    Entity *entity = new Entity(&scene_context_);
    entities_.push_back(entity);

}

}