/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adi-nata <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 09:29:43 by adi-nata          #+#    #+#             */
/*   Updated: 2023/06/27 00:51:26 by adi-nata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"

# include <stdarg.h>

typedef struct s_format
{
	va_list	arg;
	int		meno;
	int		zero;
	int		hash;
	int		spc;
	int		piu;
	int		len;
	int		wdt;
	int		prc;
	int		wdtlen;
	int		prclen;
	int		wdtquant;
	int		prcquant;
	int		hex1;
	int		x;
}	t_format;

int			ft_printf(const char *str, ...);
t_format	*ft_flag_init(t_format *flag);
int			ft_syntax(const char *str, int i, t_format *flag);
void		ft_checkflags(const char *str, int p, int i, t_format *flag);
int			ft_checkflags2(const char *str, int pp, t_format *flag);
void		ft_checkdigitflags(const char *str, int pp, t_format *flag);
int			ft_wrongflags(const char *formstr, int x, t_format *flag);
void		ft_checkformat(const char *str, int p, int i, t_format *flag);
void		ft_printfer(const char *formstr, int x, t_format *flag);

void		ft_putstrprc(char *s, t_format *flag);
void		ft_putwdt(t_format *flag);
void		ft_putwdt0(t_format *flag);
void		ft_putprc0(t_format *flag);

void		ft_managewdt(int len, t_format *flag);
void		ft_managewdtprc(int n, int len, t_format *flag);

void		hexconvert(long unsigned int n, int len,
				char *base, t_format *flag);
int			hexlen(long unsigned int n);

//	c

void		ft_printfc(char c, t_format *flag);

//	s

void		ft_printfs(char *s, t_format *flag);
void		ft_puts(char *s, int len, t_format *flag);
void		ft_checkwdts(int len, char *s, t_format *flag);

// di

void		ft_printfdi(int nbr, t_format *flag);
void		ft_printfdi2(int nbr, int len, char *snbr, t_format *flag);
void		ft_putdi(int n, char *s, int len, t_format *flag);
void		ft_checkwdtdi(int n, t_format *flag);

void		ft_checkneg(int n, t_format *flag);
void		ft_checkmeno(int n, t_format *flag);
void		ft_checkspc(int n, t_format *flag);
void		ft_checkpiu(int n, t_format *flag);

// u

void		ft_printfu(unsigned int nbr, t_format *flag);
void		ft_putu(char *s, int len, t_format *flag);
void		ft_checkwdtu(t_format *flag);

size_t		ft_unsize(long num);
void		ft_unsconvert(unsigned int n, int len, char *snbr);

// xX
void		ft_printfx(unsigned int x, t_format *flag,
				const char *fomrstr, int spec);
void		ft_putx(unsigned int n, char *base, int len, t_format *flag);
void		ft_checkwdtx(unsigned int n, t_format *flag);
void		ft_checkhash(unsigned int n, t_format *flag);

// %

void		ft_printperc(t_format *flag);
void		ft_checkwdt_perc(t_format *flag);

void		ft_printfp(unsigned long int nbr, t_format *flag);
void		ft_putp(unsigned long int n, int len, char *base, t_format *flag);

#endif
