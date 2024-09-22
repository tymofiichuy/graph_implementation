#include <gtest/gtest.h>
#include "graph.hpp"

TEST(StructureTest, LNKTest){
  EXPECT_EQ(1, 1);
}

TEST(BasicLogicTest, DWGraphVertexSearchTest){
  directed_weighted_graph dwg(5);

  EXPECT_TRUE(dwg.vertex_search(4));
}

TEST(BasicLogicTest, DWGraphEdgeSearchTest){
  directed_weighted_graph dwg(5);
  edge e(1, 2, 0);
  dwg.add_edge(e);
  
  EXPECT_TRUE(dwg.edge_search(e));
}

TEST(BasicLogicTest, DWGraphVertexDeleteTest){
  directed_weighted_graph dwg(5);
  dwg.delete_vertex(4);

  EXPECT_FALSE(dwg.vertex_search(4));
}

TEST(BasicLogicTest, DWGraphEdgeDeleteTest){
  directed_weighted_graph dwg(5);
  edge e1(1, 2, 0);
  edge e2(3, 2, 0);
  dwg.add_edge(e1);
  dwg.add_edge(e2);
  dwg.delete_edge(e2);

  EXPECT_FALSE(dwg.edge_search(e2));
}

TEST(BasicLogicTest, EdgeRedirectTest){
  edge e1(1, 2, 0);
  e1.redirect();
  edge e2(2, 1, 0);
  
  EXPECT_TRUE(e1 == e2);
}

TEST(BasicLogicTest, UdWGraphEdgeSearchTest){
  undirected_weighted_graph udwg(5);
  edge e(1, 2, 0);
  udwg.add_edge(e);
  e.redirect();
  
  EXPECT_TRUE(udwg.edge_search(e));
}

TEST(BasicLogicTest, UdWGraphDeleteEdgeTest){
  undirected_weighted_graph udwg(5);
  edge e1(1, 2, 0);
  edge e2 = e1;
  e2.redirect();
  udwg.add_edge(e1);
  
  udwg.delete_edge(e1);
  EXPECT_FALSE(udwg.edge_search(e1)||udwg.edge_search(e1));
}

TEST(BasicLogicTest, UdWGraphAddVertexTest){
  undirected_weighted_graph udwg(5);
  udwg.add_vertex(7);
  
  EXPECT_TRUE(udwg.vertex_search(7));
}

TEST(BasicLogicTest, DUwGraphAddEdgeTest){
  directed_unweighted_graph duwg(5);
  edge e1(1, 2, 3);
  edge e2(1, 2, 1);
  duwg.add_edge(e1);
  
  EXPECT_TRUE(!duwg.edge_search(e1) && duwg.edge_search(e2));
}

TEST(BasicLogicTest, UdUwGraphDeleteEdgeTest){
  undirected_weighted_graph uduwg(5);
  edge e1(1, 2, 0);
  edge e2 = e1;
  e2.redirect();
  uduwg.add_edge(e1);
  
  uduwg.delete_edge(e1);
  EXPECT_FALSE(uduwg.edge_search(e1)||uduwg.edge_search(e1));
}

TEST(BasicLogicTest, UdUwGraphAddEdgeTest){
  undirected_unweighted_graph uduwg(5);
  edge e1(1, 2, 3);
  edge e2(1, 2, 1);
  edge e3(2, 1, 1);
  uduwg.add_edge(e1);
  
  EXPECT_TRUE(uduwg.edge_search(e2) && uduwg.edge_search(e3));
}

TEST(AdvancedLogicTest, DWGraphMatrixTest){
  directed_weighted_graph dwg(2);
  edge e1(1, 2, 5);
  dwg.add_edge(e1);
  int* m = dwg.to_matrix();

  EXPECT_TRUE(m[0]==0 && m[1]==5 && m[2]==0 && m[3]==0);
  delete[] m;
}

TEST(AdvancedLogicTest, UdUwGraphMatrixTest){
  undirected_unweighted_graph uduwg(2);
  edge e1(1, 2, 1);
  uduwg.add_edge(e1);
  int* m = uduwg.to_matrix();

  EXPECT_TRUE(m[0]==0 && m[1]==1 && m[2]==1 && m[3]==0);
  delete[] m;
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}