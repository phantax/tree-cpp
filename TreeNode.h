/*
 * THE-MAN-TOOLS: A suite of useful tools for cryptography and embedded 
 * system security.
 * Copyright (C) 2015 Andreas Walz
 *
 * Author: Andreas Walz
 *
 * This file is part of THE-MAN-TOOLS.
 *
 * THE-MAN-TOOLS are free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or (at your option) any later version.
 *
 * THE-MAN-TOOLS are distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with THE-MAN-TOOLS; if not, see <http://www.gnu.org/licenses/>
 * or write to the Free Software Foundation, Inc., 51 Franklin Street,
 * Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef __TreeNode_H__
#define __TreeNode_H__

#include <stdlib.h>
#include <stdint.h>
#include <vector>


/* ==========================================================================
 *
 *
 * ========================================================================== */

class TreeNode {

public:

	/* TODO: Add description */
    typedef std::vector<TreeNode*> children_list_t;


	/* TODO: Add description */
	TreeNode() : parent_(0) {
    }


	/* TODO: Add description */
    inline void setParent(TreeNode* parent) {

        parent_ = parent;
    }    


	/* TODO: Add description */
    inline TreeNode* getParent() const {

        return parent_;
    }    


	/* TODO: Add description */
    TreeNode* getRoot() {
    
        TreeNode* root = this;
        TreeNode* parent = parent_;

        while (parent != 0) {
            root = parent;
            parent = parent->getParent();
        }

        return root;
    }    


	/* TODO: Add description */
    inline const children_list_t& getChildren() const {

        return children_;
    }    


	/* TODO: Add description */
    void listNodes(std::vector<TreeNode*>& nodes) {

        nodes.push_back(this);

        for (children_list_t::const_iterator it = children_.begin();
                it != children_.end(); ++it) {
            (*it)->listNodes(nodes);
        }
    }


	/* TODO: Add description */
    int getNNodes() const {

        int n = 1;

        for (children_list_t::const_iterator it = children_.begin();
                it != children_.end(); ++it) {
            n += (*it)->getNNodes();
        }

        return n;
    }    


	/* TODO: Add description */
    int getDepth() const {

        int depth = 0;

        for (children_list_t::const_iterator it = children_.begin();
                it != children_.end(); ++it) {
            
            int subDepth = (*it)->getDepth();
            if (subDepth > depth) {
                depth = subDepth;
            }
        }

        return depth + 1;
    }    


	/* TODO: Add description */
    inline void print() const {

        print("", 0);
    }

	/* TODO: Add description */
    void print(const std::string& prefix, size_t col) const {

        printMe(col);

        int n = children_.size();
        for (int i = 0; i < n; ++i) {
        
            string newPrefix = prefix;
            if ((i + 1) < n) {
                newPrefix += "|   ";
                std::cout << prefix + "|---";
            } else {
                /* >>> this is the last child */
                newPrefix += "    ";
                std::cout << prefix + "+---";
            }

            children_[i]->print(newPrefix, col + 4);
        }
    }

	/* TODO: Add description */
    virtual void printMe(size_t col) const {

        std::cout << "[#]" << std::endl;
    }


	/* TODO: Add description */
    bool addChild(TreeNode* child) {

        if (child == 0) {
            return false;
        }

        for (children_list_t::iterator it = children_.begin();
                it != children_.end(); ++it) {
            if (*it == child) {
                /* to-become-child seems to be already
                 * a child of this tree node */
                return false;
            }
        }

        child->setParent(this);        

        children_.push_back(child);

        return true;
    }


	/* TODO: Add description */
	virtual ~TreeNode() {
    }


private:

	/* TODO: Add description */
    TreeNode* parent_;

	/* TODO: Add description */
    children_list_t children_;


};


#endif
