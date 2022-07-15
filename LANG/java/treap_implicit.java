/**
 * Author: Sergey Kopeliovich (Burunduk30@gmail.com)
 * Date: 2014.05.27
 */

import java.util.*;
import java.io.*;

class treap_implicit { 
	static Random r = new Random();

	static class Node {
		static final Node NULL = new Node();
		Node l, r;
		int data, y, size;
		private Node() {
			l = r = this;
			size = 0;
		}
		public Node( int data, int y, Node l, Node r ) {
			this.data = data;
			this.y = y;
			this.l = l;
			this.r = r;
			calc();
		}
		void calc() {
			size = 1 + l.size + r.size;
		}
	}
	class PairNode {
		Node l, r;
		PairNode( Node l, Node r ) {
			this.l = l;
			this.r = r;
		}
	}

	PairNode split( Node v, int k ) {
		if (v == Node.NULL)
			return new PairNode(Node.NULL, Node.NULL);
		PairNode  p;
		int s = v.l.size + 1;
		if (s <= k) {
			p = split(v.r, k - s); v.r = p.l; p.l = v;
		} else {
			p = split(v.l, k); v.l = p.r; p.r = v;
		}
		v.calc();
		return p;
	}

	Node add( Node v, int i, int data, int y ) {
		if (v == Node.NULL)
			return new Node(data, y, Node.NULL, Node.NULL);
		int s = v.l.size + 1;
		if (v.y < y) 
			if (i < s)
				v.l = add(v.l, i, data, y);
			else
				v.r = add(v.r, i - s, data, y);
		else {
			PairNode p = split(v, i);
			v = new Node(data, y, p.l, p.r);
		}
		v.calc();
		return v;
	}

	Node merge( Node l, Node r ) {
		if (l == Node.NULL)
			return r;
		if (r == Node.NULL)
			return l;
		Node v;
		if (l.y < r.y) {
			v = l; l.r = merge(l.r, r);
		} else {
			v = r; r.l = merge(l, r.l);
		}
		v.calc();
		return v;
	}

	Node del( Node v, int i ) throws Exception {
		if (v == Node.NULL)
			throw new Exception("del: i-th vertex is not found");
		int s = v.l.size + 1;
		if (i == s)
			return merge(v.l, v.r);
		if (s > i)
			v.l = del(v.l, i);
		else
			v.r = del(v.r, i - s);
		v.calc();
		return v;
	}

	PrintWriter out;

	void out( Node v ) {
		if (v == Node.NULL)
			return;
		out(v.l);
		out.print(v.data + " ");
		out(v.r);
	}

	Node root = Node.NULL;
}
