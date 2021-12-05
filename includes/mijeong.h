/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mijeong.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaejeong <jaejeong@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:55:04 by dokkim            #+#    #+#             */
/*   Updated: 2021/12/05 17:18:28 by jaejeong         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIJEONG_H
# define MIJEONG_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>

typedef struct s_info
{
	int	process_count;
}	t_info;

typedef struct s_process
{
	char *instruction;
	char *option;
	char **bundle;
}	t_process;



# endif
