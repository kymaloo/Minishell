/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aafounas <aafounas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:23:34 by aafounas          #+#    #+#             */
/*   Updated: 2024/10/29 17:53:43 by aafounas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_ast_node  *create_ast_node(char *cmd, char **args)
{
    t_ast_node  *node;

    node = malloc(sizeof(t_ast_node));
    if (!node)
        return (NULL);
    node->cmd = cmd;
    node->args = args;
    node->left = NULL;
    node->right = NULL;
    node->is_pipe = 0;
    node->is_redirection = 0;
    return (node);
}